/*
A Arduino library for the AHT20 sensor

I made this library for my nodes. It has only fixed settings.
The settings can be changed in the header  file (this file)
*/
#ifndef __AHT20_SENSOR_H__
#define __AHT20_SENSOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

#define AHT20_I2C_ADDR                               0x38
#define AHT20_STATUS_REG                           0x71
#define AHT20_CMD_INIT                                0xBE
#define AHT20_CMD_INIT_PARAM1                 0x08
#define AHT20_CMD_INIT_PARAM2                 0x00
#define AHT20_CMD_MEASUR                        0xAC
#define AHT20_CMD_MEASUR_PARAM1          0x33
#define AHT20_CMD_MEASUR_PARAM2          0x00
#define AHT20_CMD_SOFT_RESET                  0xBA


class AHT20{
public:

    AHT20();
    void begin(void);
    uint8_t getStatReg();
    void startSingleMeasure(void);
    float getTemperature(void);
    float getHumidity(void);

protected:

private:

    void write8(uint8_t, uint8_t);
    uint8_t read8u(uint8_t adr);
    bool statusMeas(void);
    void reset(void);
    void readRawData(void);

    float humi;
    uint32_t humi_raw;
    float temp;
    uint32_t temp_raw;
    bool haveRawData;
    uint32_t startuptime;

};




















#endif  //__AHT20_sensor_h__
