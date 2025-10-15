/**
  ************************************************************************************
  * @file      : hc_sr04.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for hc_sr04.c file.
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

#ifndef HC_SR04_H
#define HC_SR04_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOA
#define ECHO_PIN GPIO_PIN_8
#define ECHO_PORT GPIOA
#define MIN_RANGE 2
#define MAX_RANGE 400
#define MIN_ECHO_TIME (uint32_t)(MIN_RANGE * 2 / 0.034)
#define MAX_ECHO_TIME (uint32_t)(MAX_RANGE * 2 / 0.034)
#define TIME_FOR_START_FRONT 65535
#define TIME_FOR_END_FRONT (uint32_t)((MAX_RANGE + 1) * 2 / 0.034)

// Ultrasonic Ranging Module GPIO pin description
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} HC_SR04_GpioItem;

// Set GPIO for the HC-SR04 trigger pin
void HcSr04SetGpioTrigger(HC_SR04_GpioItem trigger_gpio_item);

//  Set GPIO for the HC-SR04 echo pin
void HcSr04SetGpioEcho(HC_SR04_GpioItem echo_gpio_item);

// Set TIM handle pointer
void HcSr04SetTimHandlePointer(TIM_HandleTypeDef * p_htim);

// Trigger 10us high level signal
void HcSr04Triggert10usHighLevelSignal();

// Read the distance
int8_t HcSr04ReadDistance(uint32_t * distance);

#endif // HC_SR04_H
