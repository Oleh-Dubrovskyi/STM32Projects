/**
  ************************************************************************************
  * @file      : dth11.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for dth11.c file.
  ************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ************************************************************************************
 */

#ifndef INC_DHT11_H
#define INC_DHT11_H
/*
#define SYSTICK_LOAD (SystemCoreClock/1000000U)  // Number of System Core Clock ticks per microsecond: SYSTEM_CLOCK_TICKS_PER_US
#define SYSTICK_DELAY_CALIB (SYSTICK_LOAD >> 1)  // Microsecond time measurement error is a half of the  System Core Clock ticks number per microsecond: TIME_MEASUREMENT_ERROR

// MICROSECONDS_DELAY
#define DELAY_US(us) \
    do { \
         uint32_t start = SysTick->VAL; \
         uint32_t ticks = (us * SYSTICK_LOAD)-SYSTICK_DELAY_CALIB;  \
         while((start - SysTick->VAL) < ticks); \
    } while (0)
*/

#include <stdint.h>
#include "stm32f4xx_hal.h"

// Number of System Core Clock ticks per microsecond
//extern uint32_t  g_system_clock_ticks_per_us;
// Microsecond time measurement error is a half of the  System Core Clock ticks number per microsecond
//extern uint32_t g_time_measurement_error_us;

extern const float DHT11_SCALE;

// GPIO pin DTH11 data line description structure
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} DTH11GpioDataLine;

// DTH11 data line default pin
extern DTH11GpioDataLine g_dth11_gpio_data_line;

// Configure DHT11 data line
void Dht11ConfigureDataLine(DTH11GpioDataLine data_line);

// Send a request to the DHT11 sensor
void Dht11SendRequest();

// Get a response from the DHT11 sensor
uint8_t Dht11GetResponse();

// Get responsed bytes
uint8_t Dht11GetResponsedBytes(uint8_t * rh_byte1, uint8_t * rh_byte2,
		                       uint8_t * temp_byte1, uint8_t * temp_byte2, uint8_t * sum);

// Set DHT11 data line pin Input
void Dht11SetDataLinePinInput();

// Set DHT11 data line pin Output
void Dht11SetDataLinePinOutput();

// Enable GPIOx clock for the Dht11 data line port
void Dht11EnableGPIOXClock();

// Read byte from response
uint8_t Dht11ReadByte();

#endif // INC_DHT11_H
