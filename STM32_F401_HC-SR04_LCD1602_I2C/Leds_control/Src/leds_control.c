/**
  ***************************************************************************************
  * @file      : leds_control.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to manage the external LEDs
  ***************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ***************************************************************************************
 */

#include "leds_control.h"

// Red LED GPIO configuration value
static LedGpioControlLine s_red_led_control_line =
    {.gpio_type = RED_LED_GPIO_PORT_DEFAULT, .gpio_pin = RED_LED_PIN_DEFAULT};

// Yellow LED GPIO configuration value
static LedGpioControlLine s_yellow_led_control_line =
    {.gpio_type = YELLOW_LED_GPIO_PORT_DEFAULT, .gpio_pin = YELLOW_LED_PIN_DEFAULT};

// Green LED GPIO configuration value
static LedGpioControlLine s_green_led_control_line =
    {.gpio_type = GREEN_LED_GPIO_PORT_DEFAULT, .gpio_pin = GREEN_LED_PIN_DEFAULT};

// Switch LED ON/OFF
static void LedsControlSwitchLed(uint8_t on_off, LedColor led_color)
{
    switch (led_color)
    {
        case LED_RED:
            HAL_GPIO_WritePin(s_red_led_control_line.gpio_type,
                              s_red_led_control_line.gpio_pin, on_off ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;
        case LED_YELLOW:
            HAL_GPIO_WritePin(s_yellow_led_control_line.gpio_type,
                              s_yellow_led_control_line.gpio_pin, on_off ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;
        case LED_GREEN:
            HAL_GPIO_WritePin(s_green_led_control_line.gpio_type,
                              s_green_led_control_line.gpio_pin, on_off ? GPIO_PIN_SET : GPIO_PIN_RESET);
        	break;
        default:
        // Unsupported LED color
            break;
    }
}

// Configure GPIO for red, yellow and green LEDs
void LedsControlConfigureLedsGPIOs(LedGpioControlLine red_led,
		                           LedGpioControlLine yellow_led, LedGpioControlLine green_led)
{
	s_red_led_control_line = red_led;
	s_yellow_led_control_line = yellow_led;
	s_green_led_control_line = green_led;
}

// Set LEDs' status on distance
void LedsControlSetLedsOnDistance(uint32_t distance)
{
	if (distance <= DANGEROUS_DISTANCE)
	{
		LedsControlSwitchLed(LED_ON, LED_RED);
	}
	else if (distance > DANGEROUS_DISTANCE && distance <= ATTENTION_DISTANCE)
	{
        LedsControlSwitchLed(LED_ON, LED_RED);
        LedsControlSwitchLed(LED_ON, LED_YELLOW);
	}
	else if (distance > ATTENTION_DISTANCE && distance < SAFE_DISTANCE)
	{
        LedsControlSwitchLed(LED_ON, LED_YELLOW);
	}
	else
	{
        LedsControlSwitchLed(LED_ON, LED_GREEN);
	}
}

// Switch LEDs' OFF
void LedsControlSwitchLedsOff()
{
    LedsControlSwitchLed(LED_OFF, LED_RED);
    LedsControlSwitchLed(LED_OFF, LED_YELLOW);
    LedsControlSwitchLed(LED_OFF, LED_GREEN);
}
