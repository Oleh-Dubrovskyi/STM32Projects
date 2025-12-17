/**
  ************************************************************************************
  * @file      : delay_micro.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API for microsecond and milliseconds delays
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

#include "../Inc/delay_micro.h"

static TIM_HandleTypeDef htim2;

// Microseconds delay with SysTick
void SysTickMicrosecondsDelay(uint32_t microseconds_delay)
{
    if (microseconds_delay > 999)
    {
    	HAL_Delay(microseconds_delay/1000);
    	return;
    }

	uint32_t delay_ticks = microseconds_delay * SYSTEM_CLOCK_TICKS_PER_MICROSECOND;
	uint32_t initial_tick = SysTick->VAL;
    if (initial_tick < delay_ticks)
    {
    	SysTick->VAL = delay_ticks + TICKS_MEASUREMENT_ERROR;
    	initial_tick = SysTick->VAL;
    }

    // The SysTick->Val is constantly counting down
    while((initial_tick - SysTick->VAL) < delay_ticks);
}

// Initialize TIM2 to use it for micro-delays
void TIM2MicrosecondsDelayInit()
{
	__HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    // 1 tick = 1 us
    htim2.Init.Prescaler = (SystemCoreClock / 1000000U) - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    // 32-bit maximum value
    htim2.Init.Period = 65535;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start(&htim2);
}

// Microseconds delay with TIM2
void TIM2MicrosecondsDelay(uint32_t microseconds_delay)
{
    //uint32_t initial_tick = __HAL_TIM_GET_COUNTER(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0); // Reset the counter
    while (__HAL_TIM_GET_COUNTER(&htim2) < microseconds_delay);
}

// Milliseconds delay with TIM2
void TIM2MillisecondsDelay(uint32_t milliseconds_delay)
{
    while(milliseconds_delay--)
    {
    	TIM2MicrosecondsDelay(1000);
    }
}
