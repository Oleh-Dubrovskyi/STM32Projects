/**
  ************************************************************************************
  * @file      : uart.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for uart.c file.
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

#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define UART_TIMEOUT_SEC 1000
#define UART_CHANNEL_TIMEOUT 5000
#define BS '\x08'
#define ESC '\x1b'
#define DEL '\x7f'
#define LF '\n'
#define CRET '\r'

// Do perform a handshake communication to ensure the UART channel is ready
HAL_StatusTypeDef UartReady(UART_HandleTypeDef * uart_handle_type_def);

// Send string to UART channel
HAL_StatusTypeDef UartSendString(UART_HandleTypeDef * uart_handle_type_def, const char * string,
		                         uint16_t string_size, uint32_t timeout_ms);

// Receive a command through the UART channel
HAL_StatusTypeDef UartReceiveCommand(UART_HandleTypeDef * uart_handle_type_def,
		                             uint8_t * data_buffer, uint16_t data_size, uint32_t timeout_ms);

#endif // UART_H
