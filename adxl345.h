/*
 * adxl345.h
 *
 *  Created on: Jul 28, 2023
 *      Author: Le Anh
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "app.h"
#include "em_i2c.h"
#include <stdio.h>

#define SCL_PORT gpioPortD
#define SCL_PIN 2
#define SDA_PORT gpioPortD
#define SDA_PIN 3

#define ADXL345_ADDRESS 0x53<<1 // adxl345_address
#define DEVICE_ID 0xE5

#define ADXL345_REG_DEVID 0x00        ///< Device ID
#define ADXL345_REG_THRESH_TAP 0x1D   ///< Tap threshold
#define ADXL345_REG_OFSX 0x1E         ///< X-axis offset
#define ADXL345_REG_OFSY 0x1F         ///< Y-axis offset
#define ADXL345_REG_OFSZ 0x20         ///< Z-axis offset
#define ADXL345_REG_DUR 0x21          ///< Tap duration
#define ADXL345_REG_LATENT 0x22       ///< Tap latency
#define ADXL345_REG_WINDOW 0x23       ///< Tap window
#define ADXL345_REG_THRESH_ACT 0x24   ///< Activity threshold
#define ADXL345_REG_THRESH_INACT 0x25 ///< Inactivity threshold
#define ADXL345_REG_TIME_INACT 0x26   ///< Inactivity time
#define ADXL345_REG_ACT_INACT_CTL 0x27 ///< Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF 0x28 ///< Free-fall threshold
#define ADXL345_REG_TIME_FF 0x29   ///< Free-fall time
#define ADXL345_REG_TAP_AXES 0x2A  ///< Axis control for single/double tap
#define ADXL345_REG_ACT_TAP_STATUS 0x2B ///< Source for single/double tap
#define ADXL345_REG_BW_RATE 0x2C        ///< Data rate and power mode control
#define ADXL345_REG_POWER_CTL 0x2D      ///< Power-saving features control
#define ADXL345_REG_INT_ENABLE 0x2E     ///< Interrupt enable control
#define ADXL345_REG_INT_MAP 0x2F        ///< Interrupt mapping control
#define ADXL345_REG_INT_SOURCE 0x30     ///< Source of interrupts
#define ADXL345_REG_DATA_FORMAT 0x31    ///< Data format control
#define ADXL345_REG_DATAX0 0x32         ///< X-axis data 0
#define ADXL345_REG_DATAX1 0x33         ///< X-axis data 1
#define ADXL345_REG_DATAY0 0x34         ///< Y-axis data 0
#define ADXL345_REG_DATAY1 0x35         ///< Y-axis data 1
#define ADXL345_REG_DATAZ0 0x36         ///< Z-axis data 0
#define ADXL345_REG_DATAZ1 0x37         ///< Z-axis data 1
#define ADXL345_REG_FIFO_CTL 0x38       ///< FIFO control
#define ADXL345_REG_FIFO_STATUS 0x39    ///< FIFO status

typedef enum
{
  ADXL345_DATARATE_3200_HZ    = 0b1111, // 1600Hz Bandwidth   140µA IDD
  ADXL345_DATARATE_1600_HZ    = 0b1110, //  800Hz Bandwidth    90µA IDD
  ADXL345_DATARATE_800_HZ     = 0b1101, //  400Hz Bandwidth   140µA IDD
  ADXL345_DATARATE_400_HZ     = 0b1100, //  200Hz Bandwidth   140µA IDD
  ADXL345_DATARATE_200_HZ     = 0b1011, //  100Hz Bandwidth   140µA IDD
  ADXL345_DATARATE_100_HZ     = 0b1010, //   50Hz Bandwidth   140µA IDD
  ADXL345_DATARATE_50_HZ      = 0b1001, //   25Hz Bandwidth    90µA IDD
  ADXL345_DATARATE_25_HZ      = 0b1000, // 12.5Hz Bandwidth    60µA IDD
  ADXL345_DATARATE_12_5_HZ    = 0b0111, // 6.25Hz Bandwidth    50µA IDD
  ADXL345_DATARATE_6_25HZ     = 0b0110, // 3.13Hz Bandwidth    45µA IDD
  ADXL345_DATARATE_3_13_HZ    = 0b0101, // 1.56Hz Bandwidth    40µA IDD
  ADXL345_DATARATE_1_56_HZ    = 0b0100, // 0.78Hz Bandwidth    34µA IDD
  ADXL345_DATARATE_0_78_HZ    = 0b0011, // 0.39Hz Bandwidth    23µA IDD
  ADXL345_DATARATE_0_39_HZ    = 0b0010, // 0.20Hz Bandwidth    23µA IDD
  ADXL345_DATARATE_0_20_HZ    = 0b0001, // 0.10Hz Bandwidth    23µA IDD
  ADXL345_DATARATE_0_10_HZ    = 0b0000  // 0.05Hz Bandwidth    23µA IDD (default value)
} dataRate_t;


typedef enum
{
  ADXL345_RANGE_16_G          = 0b11,   // +/- 16g
  ADXL345_RANGE_8_G           = 0b10,   // +/- 8g
  ADXL345_RANGE_4_G           = 0b01,   // +/- 4g
  ADXL345_RANGE_2_G           = 0b00    // +/- 2g (default value)
} range_t;


void initCMU(void);
void i2c_transfer(uint16_t device_addr, uint8_t cmd_array[], uint8_t data_array[], uint16_t cmd_len, uint16_t data_len, uint8_t flag);
void i2c_Write(uint8_t addr, uint8_t data);
uint8_t i2c_Read(uint8_t reg_offset);
void i2c_Init();
void init_adxl();
void read_accel_data(int *x, int *y, int *z);
void read_acc(int *xyz);
void get_acc(double *xyz);
void setActivityThreshold(int activityThreshold);
void setInactivityThreshold(int inactivityThreshold);
void setTimeInactivity(int timeInactivity);

#endif /* ADXL345_H_ */
