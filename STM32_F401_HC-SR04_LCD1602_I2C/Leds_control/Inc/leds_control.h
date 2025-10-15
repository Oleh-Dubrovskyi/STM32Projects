/**
  ************************************************************************************
  * @file      : leds_control.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for leds_control.c file.
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

#ifndef LEDS_CONTROL
#define LEDS_CONTROL

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define DANGEROUS_DISTANCE 10
#define ATTENTION_DISTANCE 30
#define SAFE_DISTANCE 50

#define RED_LED_PIN_DEFAULT GPIO_PIN_4
#define RED_LED_GPIO_PORT_DEFAULT GPIOB
#define YELLOW_LED_PIN_DEFAULT GPIO_PIN_5
#define YELLOW_LED_GPIO_PORT_DEFAULT GPIOB
#define GREEN_LED_PIN_DEFAULT GPIO_PIN_6
#define GREEN_LED_GPIO_PORT_DEFAULT GPIOB
#define LED_OFF 0
#define LED_ON 1

// GPIO pin description structure for the external LEDs
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} LedGpioControlLine;

typedef enum
{
	LED_RED,
	LED_YELLOW,
	LED_GREEN
} LedColor;

// Configure GPIO for red, yellow and green LEDs
void LedsControlConfigureLedsGPIOs(LedGpioControlLine red_led,
		                           LedGpioControlLine yellow_led, LedGpioControlLine green_led);

// Set LEDs' status on distance
void LedsControlSetLedsOnDistance(uint32_t distance);

// Switch LEDs' OFF
void LedsControlSwitchLedsOff();

#endif // LEDS_CONTROL
