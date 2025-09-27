/**
  ****************************************************************************************************
  * @file      : uart.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to get commands from UART channel and to send results
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ****************************************************************************************************
 */

#include <string.h>
#include <stdio.h>

#include "../Inc/uart.h"

static const char DELETE[] = "\x7f";
static const char ENTER[] = "\r\n";
static const char HELLO[] = "\r\nHello! Please, say \"Hello\" to check UART channel\r\n>>";
static const char RESPONSE[] = "Hello";

// Check if the character is a letter
static uint8_t IsLatinLetter(uint8_t symbol)
{

    if ((symbol >=65 && symbol <=90) || (symbol >=97 && symbol <= 122))
    {
        return 1;
    }

    return 0;
}

// Receive one symbol from UART
static HAL_StatusTypeDef UartReceiveSymbol(UART_HandleTypeDef * uart_handle_type_def, uint8_t * symbol, uint32_t timeout_ms)
{
	return HAL_UART_Receive(uart_handle_type_def, symbol, 1, timeout_ms);
}

// Do perform a handshake communication to ensure the UART channel is ready
HAL_StatusTypeDef UartReady(UART_HandleTypeDef * uart_handle_type_def)
{
	HAL_StatusTypeDef hal_status = HAL_ERROR;
    char response[20];

	hal_status = HAL_UART_Transmit(uart_handle_type_def, (uint8_t *)HELLO, strlen(HELLO), UART_TIMEOUT_SEC);

	if (hal_status != HAL_OK)
    {
	    return hal_status;
    }

	while (1)
	{
        // Wait for response to ensure the UART channel is OK
		hal_status = UartReceiveCommand(uart_handle_type_def, (uint8_t *)response, 6, UART_CHANNEL_TIMEOUT);
        if (hal_status != HAL_OK)
        {
            return hal_status;
        }
        if (!strcmp(response, RESPONSE))
        {
            break;
        }
	}

	return hal_status;
}

// Send string to UART channel
HAL_StatusTypeDef UartSendString(UART_HandleTypeDef * uart_handle_type_def, const char * string,
		                         uint16_t string_size, uint32_t timeout_ms)
{
    return HAL_UART_Transmit(uart_handle_type_def, (uint8_t *)string, strlen(string), timeout_ms);
}

// Receive a command through the UART channel
HAL_StatusTypeDef UartReceiveCommand(UART_HandleTypeDef * uart_handle_type_def,
		                             uint8_t command[], uint16_t data_size, uint32_t timeout_ms)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    uint8_t symbol;
    uint8_t idx = 0;

    memset(command, 0, data_size);
    while (1)
    {
        // Get command name "symbol by symbol"
   	    if((status = UartReceiveSymbol(uart_handle_type_def, &symbol, timeout_ms)) != HAL_OK)
        {
            // Failed to receive next command name character
   	    	return status;
        }

   	   	switch (symbol)
   	   	{
   	   	    case BS:
   	   	    case DEL:
   	   	    case ESC:
   	            // Backspace, Delete or ESC was received. Remove previous symbol from command and from terminal
   	    	    if (idx > 0)
   	    	    {
   	    		    idx--;
   				    status = HAL_UART_Transmit(uart_handle_type_def, (uint8_t *)DELETE, strlen(DELETE), timeout_ms);
   				    if (status != HAL_OK)
   				    {
   					    return status;
   				    }
   	    	    }
   	   	        break;
   	   	    case CRET:
   	   	    case LF:
   	        	// Pressed ENTER means the end of the command name
   	        	command[idx] = 0;
   		    	status = HAL_UART_Transmit(uart_handle_type_def, (uint8_t *)ENTER, strlen(ENTER), timeout_ms);
   	            return status;
   	   	    default:
   	   	    	if (IsLatinLetter(symbol))
   	   	    	{
   	   	    	    // Next command name latter was received
   	   	    	    if ((idx < (data_size - 1)))
   	   	    	    {
   	   	    	        command[idx] = symbol;
   	   	    	        status = HAL_UART_Transmit(uart_handle_type_def, &command[idx], 1, timeout_ms);
   	   	    	        idx++;
   	   	    	    }
   	   	    	}
   	   	    	else
   	   	    	{
   	   	    	    // Unexpected symbol was received. Do nothing
   	   	    	}
   	            break;
   	   	}
    }

    return status;
}

