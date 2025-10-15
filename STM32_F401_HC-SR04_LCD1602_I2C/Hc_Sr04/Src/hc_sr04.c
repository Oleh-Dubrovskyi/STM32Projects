/**
  **********************************************************************************************
  * @file      : hc_sr04.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to manage the Ultrasonic Ranging Module HC-SR04
  **********************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************
 */

#include "hc_sr04.h"
#include "../../DelayMicro/Inc/delay_micro.h"

static HC_SR04_GpioItem s_hc_sr04_gpio_trig;
static HC_SR04_GpioItem s_hc_sr04_gpio_echo;
static TIM_HandleTypeDef * s_p_htim;

// Set GPIO for the HC-SR04 trigger pin
void HcSr04SetGpioTrigger(HC_SR04_GpioItem trigger_gpio_item)
{
	s_hc_sr04_gpio_trig.gpio_pin = trigger_gpio_item.gpio_pin;
	s_hc_sr04_gpio_trig.gpio_type = trigger_gpio_item.gpio_type;
}

// Set GPIO for the HC-SR04 echo pin
void HcSr04SetGpioEcho(HC_SR04_GpioItem echo_gpio_item)
{
	s_hc_sr04_gpio_echo.gpio_pin = echo_gpio_item.gpio_pin;
	s_hc_sr04_gpio_echo.gpio_type = echo_gpio_item.gpio_type;
}

// Set TIM handle pointer
void HcSr04SetTimHandlePointer(TIM_HandleTypeDef * p_htim)
{
	s_p_htim = p_htim;
}

// Trigger 10us high level signal
void HcSr04Triggert10usHighLevelSignal()
{
    HAL_GPIO_WritePin(s_hc_sr04_gpio_trig.gpio_type, s_hc_sr04_gpio_trig.gpio_pin, GPIO_PIN_SET);
    TIM2MicrosecondsDelay(10);
    HAL_GPIO_WritePin(s_hc_sr04_gpio_trig.gpio_type, s_hc_sr04_gpio_trig.gpio_pin, GPIO_PIN_RESET);
}

// Read the distance
int8_t HcSr04ReadDistance(uint32_t * distance)
{
	__HAL_TIM_SET_COUNTER(s_p_htim, 0);
	 *distance = MAX_RANGE + 1;
	 uint32_t tim_counter_start_echo = __HAL_TIM_GET_COUNTER (s_p_htim);
	 uint32_t tim_counter_fin_echo = tim_counter_start_echo;
	 uint32_t echo_time = tim_counter_fin_echo;

	 while (!HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN))
    {
        if ((tim_counter_start_echo = __HAL_TIM_GET_COUNTER (s_p_htim)) >= TIME_FOR_START_FRONT)
    	{
    		// HC-SR04 did not respond
    		*distance = 0;
    		return -1;
    	}
    }

    tim_counter_start_echo = __HAL_TIM_GET_COUNTER (s_p_htim);

    tim_counter_fin_echo = tim_counter_start_echo;

    while (HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN))
    {
    	if ((__HAL_TIM_GET_COUNTER (s_p_htim) - tim_counter_start_echo) > TIME_FOR_END_FRONT)
        {
            // The respond time is greater than MAX_RANGE * 2 / 0.034
            *distance = MAX_RANGE + 1;
            return 1;
    	}
    }

    tim_counter_fin_echo = __HAL_TIM_GET_COUNTER (s_p_htim);

    echo_time = tim_counter_fin_echo - tim_counter_start_echo;

    if (echo_time < MIN_ECHO_TIME)
    {
        *distance = MIN_RANGE - 1;
    	return -1;
    }

    if ((echo_time >= MIN_ECHO_TIME) && (echo_time <= MAX_ECHO_TIME))
    {
    	*distance = echo_time * 0.034/2;
    	return 0;
    }

    if (echo_time > MAX_ECHO_TIME)
     {
        *distance = MAX_RANGE + 1;
     	return 1;
     }

    return 1;
}
