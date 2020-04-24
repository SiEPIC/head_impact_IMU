/**
* Copyright (c) 2018 makerdiary
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above
*   copyright notice, this list of conditions and the following
*   disclaimer in the documentation and/or other materials provided
*   with the distribution.

* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef NRF52832_MDK_H
#define NRF52832_MDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LEDs definitions for nRF52832-MDK
#define LEDS_NUMBER    3

#define LED_START      22
#define LED_1          22
#define LED_2          23
#define LED_3          24
#define LED_STOP       24

#define LEDS_ACTIVE_STATE 0

#define LEDS_INV_MASK  LEDS_MASK

#define LEDS_LIST { LED_1, LED_2, LED_3 }

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2
#define BSP_LED_2      LED_3

#define BUTTONS_NUMBER 4
#define BUTTON_1       27    // Connect Grove-Button at Base Dock Grove Port#1
#define BUTTON_2       29    // Connect Grove-Button at Base Dock Grove Port#2
#define BUTTON_3       31    // Connect Grove-Button at Base Dock Grove Port#3
#define BUTTON_4       3     // Connect Grove-Button at Base Dock Grove Port#4

#define BUTTON_PULL    NRF_GPIO_PIN_PULLDOWN

#define BUTTONS_ACTIVE_STATE 1

#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4}

#define BSP_BUTTON_0   BUTTON_1
#define BSP_BUTTON_1   BUTTON_2
#define BSP_BUTTON_2   BUTTON_3
#define BSP_BUTTON_3   BUTTON_4


#define RX_PIN_NUMBER  19
#define TX_PIN_NUMBER  20
#define HWFC           false

//===================SPI PINOUT========================//
#define SPI_ICM20649_CS_PIN     29
#define SPI_ADXL372_CS_PIN      30
#define SPI_MT25QL256ABA_CS_PIN 27
#define SPI_MOSI_PIN            4
#define SPI_MISO_PIN            28
#define SPI_SCK_PIN             3
#define FLASH_SPI_SCK_PIN       6
#define FLASH_SPI_MOSI_PIN      8
#define FLASH_SPI_MISO_PIN      13

//===================I2C PINOUT========================//
// I2C pin assignment
#define I2C_SDA                 15
#define I2C_SCL                 16


#ifdef __cplusplus
}
#endif

#endif // NRF52832_MDK_H
