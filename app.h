/***************************************************************************//**
 * @file
 * @brief Application interface provided to main().
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef APP_H
#define APP_H
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "feature.h"
#include "Timer0.h"
#include "adxl345.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_iadc.h"

// size's window and overlap array
#define WINDOW_SIZE 10
#define OVERLAP_SIZE 5

// threshold to recognize an activity
#define TH_RMS_X 0.409
#define TH_STD_X1 0.05
#define TH_RMS_Y 0.206
#define TH_IQR_X 0.405
#define TH_RANGE_Y 1.375
#define TH_MEAN_Y 0.301
#define TH_STD_X2 0.253

#define DECISION_TIME1 3
#define DECISION_TIME2 2

#define LED_PORT gpioPortB
#define LED_PIN 4


// Set CLK_ADC to 10 MHz
#define CLK_SRC_ADC_FREQ        20000000  // CLK_SRC_ADC
#define CLK_ADC_FREQ            10000000  // CLK_ADC - 10 MHz max in normal mode

#define IADC_INPUT_0_PORT_PIN     iadcPosInputPortBPin0;

#define IADC_INPUT_0_BUS          BBUSALLOC
#define IADC_INPUT_0_BUSALLOC     GPIO_BBUSALLOC_BEVEN0_ADC0

#define EM2DEBUG





/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void);

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void);

#endif // APP_H
