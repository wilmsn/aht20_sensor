/*

*/
#include "aht20_sensor.h"

//************************************************************************
//Constructor: Wire Lib öffnen

AHT20::AHT20() {
  Wire.begin();
  startuptime = millis();
  haveRawData = false;
}

void AHT20::begin() {
  uint8_t reg;
  // startuptime is at least 40ms (datasheet page 8 Chap. 5.4)
  while (millis() - startuptime < 50) { delay(10); } 
  // Initialisieren
  Wire.beginTransmission(AHT20_I2C_ADDR);
  Wire.write(AHT20_CMD_INIT);
  Wire.write(AHT20_CMD_INIT_PARAM1);
  Wire.write(AHT20_CMD_INIT_PARAM2);
  Wire.endTransmission();
  getStatReg();
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

uint8_t AHT20::getStatReg() {
    return read8u(AHT20_STATUS_REG);
}

//*************************************************************************
// Einlesen von 1 Byte (unsigned) ueber die I2C-Schnittstelle

uint8_t AHT20::read8u(uint8_t adr)
{
    Wire.beginTransmission(AHT20_I2C_ADDR);
    Wire.write(adr);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)AHT20_I2C_ADDR, (uint8_t)1);
    return (uint8_t)Wire.read();
}


