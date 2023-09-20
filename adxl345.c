/*
 * adxl345.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Le Anh
 */

#include "adxl345.h"
#include "em_i2c.h"
#define CMD_ARRAY_SIZE        1
#define DATA_ARRAY_SIZE       10

uint8_t cmd_array[CMD_ARRAY_SIZE];
uint8_t data_array[DATA_ARRAY_SIZE];

void initCMU(void)
{
  CMU_ClockEnable(cmuClock_I2C0, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
}

void i2c_transfer(uint16_t device_addr, uint8_t cmd_array[], uint8_t data_array[], uint16_t cmd_len, uint16_t data_len, uint8_t flag)
{
      // Transfer structure
      I2C_TransferSeq_TypeDef i2cTransfer;

      // Initialize I2C transfer
      I2C_TransferReturn_TypeDef result;
      i2cTransfer.addr          = device_addr;
      i2cTransfer.flags         = flag;
      i2cTransfer.buf[0].data   = cmd_array;
      i2cTransfer.buf[0].len    = cmd_len;

      // Note that WRITE_WRITE this is tx2 data
      i2cTransfer.buf[1].data   = data_array;
      i2cTransfer.buf[1].len    = data_len;

      // Set up the transfer
      result = I2C_TransferInit(I2C0, &i2cTransfer);

      // Do it until the transfer is done
      while (result != i2cTransferDone)
      {

            result = I2C_Transfer(I2C0);
      }
}

// Read a config register on an I2C device
// Tailored for the ADX345 device only i.e. 1 byte of TX
void i2c_Write(uint8_t reg_offset, uint8_t write_data)
{
      cmd_array[0] = reg_offset;
      data_array[0] = write_data;
      i2c_transfer(ADXL345_ADDRESS, cmd_array, data_array, 1, 1, I2C_FLAG_WRITE_WRITE);
}

uint8_t i2c_Read(uint8_t reg_offset){
  cmd_array[0] = reg_offset;
  i2c_transfer(ADXL345_ADDRESS, cmd_array, data_array, 1, 1, I2C_FLAG_WRITE_READ);
        return data_array[0];
}
void i2c_Init(){
        // init
        I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
        i2cInit.enable = true;
        i2cInit.master = true; /* master mode only */
        i2cInit.freq = I2C_FREQ_STANDARD_MAX;
            //i2cInit.refFreq = init->i2cRefFreq;
        i2cInit.clhr = i2cClockHLRStandard;



        // route I2C pin to GPIO


        GPIO->I2CROUTE[0].SDAROUTE = (GPIO->I2CROUTE[0].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK)
                                  | (gpioPortD << _GPIO_I2C_SDAROUTE_PORT_SHIFT
                                  | (3 << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
        GPIO->I2CROUTE[0].SCLROUTE = (GPIO->I2CROUTE[0].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK)
                                  | (gpioPortD << _GPIO_I2C_SCLROUTE_PORT_SHIFT
                                  | (2 << _GPIO_I2C_SCLROUTE_PIN_SHIFT));
        GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;

        I2C_Init(I2C0, &i2cInit);

        // enable clock
        I2C0->CTRL = I2C_CTRL_AUTOSN;
}

void init_adxl(){
  // detect device
  uint16_t value = i2c_Read(ADXL345_REG_DEVID);

            // Set an LED OFF if Master can read the fix address 's adxl345 successfully
            if (value == DEVICE_ID)
            {
                  GPIO_PinOutClear  (gpioPortA, 4);
            }
            // set full resolution and range +/- 16g
            i2c_Write(ADXL345_REG_DATA_FORMAT,0x0B);
            // set data rate
            i2c_Write(ADXL345_REG_BW_RATE, ADXL345_DATARATE_50_HZ);
            // start measurement
            i2c_Write(ADXL345_REG_POWER_CTL, 0x08);
}


void read_accel_data(int *x, int *y, int *z)
{

      // Measurement data starts at DATAX0, and ends at DATAZ1, 6 bytes long
      cmd_array[0] = ADXL345_REG_DATAX0;

      // Read 6 bytes at once
      i2c_transfer(ADXL345_ADDRESS, cmd_array, data_array, 1, 6, I2C_FLAG_WRITE_READ);

      // Now pack the return structure with meaningful data
      *x = (short)((((unsigned short)data_array[1]) << 8) | data_array[0]);
      *y = (short)((((unsigned short)data_array[3]) << 8) | data_array[2]);
      *z = (short)((((unsigned short)data_array[5]) << 8) | data_array[4]);
}
void read_acc(int *xyz){
  read_accel_data(xyz, xyz + 1, xyz + 2);
}
void get_acc(double *xyz){
  int xyz_int[3];
  int i;
  double gains[3];
  //measure three physical values
  gains[0] = 0.00376390;
  gains[1] = 0.00376009;
  gains[2] = 0.00349265;
  read_acc(xyz_int);
  for (i = 0; i < 3; i++) {
          xyz[i] = xyz_int[i] * gains[i];
      }

}
void setActivityThreshold(int activityThreshold){
  if(activityThreshold>= 0 && activityThreshold<= 255){
      activityThreshold  = activityThreshold;
  }
  else if(activityThreshold < 0){
      activityThreshold = 0;
  }
  else activityThreshold = 255;

  i2c_Write(ADXL345_REG_THRESH_ACT,activityThreshold);
}

void setInactivityThreshold(int inactivityThreshold){
  if(inactivityThreshold>= 0 && inactivityThreshold<= 255){
      inactivityThreshold  = inactivityThreshold;
    }
    else if(inactivityThreshold < 0){
        inactivityThreshold = 0;
    }
    else inactivityThreshold = 255;

    i2c_Write(ADXL345_REG_THRESH_INACT,inactivityThreshold);

}

void setTimeInactivity(int timeInactivity){
  if(timeInactivity>= 0 && timeInactivity<= 255){
      timeInactivity  = timeInactivity;
      }
      else if(timeInactivity < 0){
          timeInactivity = 0;
      }
      else timeInactivity = 255;

  i2c_Write(ADXL345_REG_TIME_INACT,timeInactivity);
}

