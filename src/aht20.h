/*
A Arduino library for the AHT20 sensor

I made this library for my nodes. It has only fixed settings.
The settings can be changed in the header  file (this file)
*/
#ifndef __AHT20_sensor_h__
#define __AHT20_sensor_h__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

#define AHT20_I2C_ADDRESS       0x71
#define AHT20_STATUS_REG        0x71
#define AHT20_I2C_ADDR          0x38


///< Default I2C address of AHT20 sensor 
#define CMD_INIT                     0xBE  ///< Init command
#define CMD_INIT_PARAMS_1ST          0x08  ///< The first parameter of init command: 0x08
#define CMD_INIT_PARAMS_2ND          0x00  ///< The second parameter of init command: 0x00
#define CMD_INIT_TIME                10    ///< Waiting time for init completion: 10ms
#define CMD_MEASUREMENT              0xAC  ///< Trigger measurement command
#define CMD_MEASUREMENT_PARAMS_1ST   0x33  ///< The first parameter of trigger measurement command: 0x33
#define CMD_MEASUREMENT_PARAMS_2ND   0x00  ///< The second parameter of trigger measurement command: 0x00
#define CMD_MEASUREMENT_TIME         80    ///< Measurement command completion time: 80ms
#define CMD_MEASUREMENT_DATA_LEN     6     ///< Return length when the measurement command is without CRC check.
#define CMD_MEASUREMENT_DATA_CRC_LEN 7     ///< Return data length when the measurement command is with CRC check.
#define CMD_SOFT_RESET               0xBA  ///< Soft reset command
#define CMD_SOFT_RESET_TIME          20    ///< Soft reset time: 20ms
#define CMD_STATUS                   0x71  ///< Get status word command


class AHT20{
public:
  /**
   * @fn AHT20
   * @brief AHT20 constructor
   * @return NONE
   */
    AHT20();
  
    void begin();

    void startSingleMeasure(void);

    float getTemperature();

    float getHumidity(void);

protected:

private:

    void write8(uint8_t, uint8_t);
    bool statusMeas(void);
    void reset(void);
    
    float temp;
    float humi;
    uint32_t startuptime;

};




















#endif  //__AHT20_sensor_h__
