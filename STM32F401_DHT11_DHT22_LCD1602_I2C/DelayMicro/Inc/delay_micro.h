/**
  ************************************************************************************
  * @file      : delay_micro.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for delay_micro.c file.
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

#ifndef INC_DELAY_MICRO_H
#define INC_DELAY_MICRO_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

// Number of System Core Clock ticks per microsecond
#define SYSTEM_CLOCK_TICKS_PER_MICROSECOND (SystemCoreClock/1000000U)
// A half of the System Core Clock ticks number per microsecond
#define TICKS_MEASUREMENT_ERROR (SYSTEM_CLOCK_TICKS_PER_MICROSECOND >> 1)

// Microseconds delay with SysTick
void SysTickMicrosecondsDelay(uint32_t microseconds_delay);

// Initialize TIM2 to use for micro-delays
void TIM2MicrosecondsDelayInit();

// Microseconds delay with TIM2
void TIM2MicrosecondsDelay(uint32_t microseconds_delay);

// Milliseconds delay with TIM2
void TIM2MillisecondsDelay(uint32_t milliseconds_delay);

#endif // INC_DELAY_MICRO_H
