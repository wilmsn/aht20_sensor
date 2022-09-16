/*

*/
#include "aht20_sensor.h"

//************************************************************************
//Constructor: Wire Lib öffnen

AHT20::AHT20(void) {
}

void AHT20::begin(void) {
  Wire.begin();
  haveRawData = false;
  // startuptime is at least 40ms (datasheet page 8 Chap. 5.4)
  delay(50);
  // Initialisieren
  Wire.beginTransmission(AHT20_I2C_ADDR);
  Wire.write(AHT20_CMD_INIT);
  Wire.write(AHT20_CMD_INIT_PARAM1);
  Wire.write(AHT20_CMD_INIT_PARAM2);
  Wire.endTransmission();
  // Das Calibration Bit muss gesetzt sein, wenn nicht reset() durchführen
  while ( getStatReg() & AHT20_CALLIBRATION_BIT == 0 ) {
    reset();
  }
}

void AHT20::startSingleMeasure(void) {
  Wire.beginTransmission(AHT20_I2C_ADDR);
  Wire.write(AHT20_CMD_MEASUR);
  Wire.write(AHT20_CMD_MEASUR_PARAM1);
  Wire.write(AHT20_CMD_MEASUR_PARAM2);
  Wire.endTransmission();
  haveRawData = false;
}

void AHT20::readRawData(void) {
    while ( getStatReg() & AHT20_BUSY_BIT > 0 ) delay(1);
    if (Wire.requestFrom((uint8_t)AHT20_I2C_ADDR, (uint8_t)6) > 0) {
        uint8_t state = Wire.read();
        humi_raw = 0;
        humi_raw |= (uint32_t)Wire.read() << 16;
        humi_raw |= (uint32_t)Wire.read() <<  8;
        uint8_t midByte = Wire.read();
        humi_raw |= midByte;
        humi_raw >>= 4;

        temp_raw = 0;
        temp_raw = ((uint32_t)midByte & 0x0000000F) << 16;
        temp_raw |= (uint32_t)Wire.read() << 8;
        temp_raw |= (uint32_t)Wire.read();
        haveRawData = true;
    }
}

float AHT20::getTemperature(void) {
    if ( ! haveRawData ) readRawData();
    return ((float)temp_raw / 1048576) * 200 - 50;
}

float AHT20::getHumidity(void) {
    if ( ! haveRawData ) readRawData();
    return  ((float)humi_raw / 1048576) * 100;
}

uint8_t AHT20::getStatReg(void) {
    Wire.beginTransmission(AHT20_I2C_ADDR);
    Wire.write(AHT20_STATUS_REG);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)AHT20_I2C_ADDR, (uint8_t)1);
    return (uint8_t)Wire.read();
}

void AHT20::reset(void) {
  Wire.beginTransmission(AHT20_I2C_ADDR);
  Wire.write(AHT20_CMD_SOFT_RESET);
  Wire.endTransmission();
  delay(100);
}


