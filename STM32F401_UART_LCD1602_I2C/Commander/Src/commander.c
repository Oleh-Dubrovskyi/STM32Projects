/**
  *******************************************************************************************************************
  * @file      : commander.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to initialize UARTs' commands list and send such commands to LCD1602
  *******************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *******************************************************************************************************************
 */

#include <string.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"

#include "commander.h"
#include "../../Lcd1602_i2c_tests/Inc/lcd1602_i2c_tests.h"
#include "../../Lcd1602_i2c/Inc/lcd1602_i2c.h"
#include "../../Uart/Inc/uart.h"

static const char WAIT_FOR_COMMAND_TO_BE_FINISHED[] = "*Wait for command to be finished*\r\n";
static const char WRONG_COMMAND_TYPE[] = "*Wrong command type. Check the code*\r\n>>";
static const char SUCCEEDED[] = "*Succeeded*\r\n>>";
static const char UNSUPPORTED_COMMAND[] = "*Wrong (unsupported) command. Try again*\r\n>>";
static const char HELP[] = "You can try such commands as:\r\n";
static const char SHOW_HELP_COMMAND[] = "ShowHelp";
static UART_HandleTypeDef * s_uart_handler;

static HAL_StatusTypeDef ShowHelp();

// Commands list
const Command COMMANDS[COMMANDS_COUNT] =
{
    {.name = "ShowHelp",           .command.command1 = ShowHelp,           .command_type = COMMAND_TYPE_1},
    {.name = "ClearScreen",        .command.command2 = ClearScreenTest,        .command_type = COMMAND_TYPE_2},
    {.name = "ShowCursor",         .command.command2 = ShowCursorTest,         .command_type = COMMAND_TYPE_2},
    {.name = "SettingCursor",      .command.command2 = SetCursorPositionTest,  .command_type = COMMAND_TYPE_2},
    {.name = "MoveCursorToRight",  .command.command2 = MoveCursorToRightTest,  .command_type = COMMAND_TYPE_2},
    {.name = "MoveCursorToLeft",   .command.command2 = MoveCursorToLeftTest,   .command_type = COMMAND_TYPE_2},
    {.name = "ReturnCursor",       .command.command2 = ReturnCursorTest,       .command_type = COMMAND_TYPE_2},
    {.name = "HideCursor",         .command.command2 = HideCursorTest,         .command_type = COMMAND_TYPE_2},
    {.name = "BlinkCursorOn",      .command.command2 = BlinkCursorOnTest,      .command_type = COMMAND_TYPE_2},
    {.name = "BlinkCursorOff",     .command.command2 = BlinkCursorOffTest,     .command_type = COMMAND_TYPE_2},
    {.name = "WriteString",        .command.command2 = WriteStringTest,        .command_type = COMMAND_TYPE_2},
    {.name = "WriteNumber",        .command.command2 = WriteNumberTest,        .command_type = COMMAND_TYPE_2},
    {.name = "WriteFloat",         .command.command2 = WriteFloatTest,         .command_type = COMMAND_TYPE_2},
    {.name = "HideDisplay",        .command.command2 = HideDisplayTest,        .command_type = COMMAND_TYPE_2},
    {.name = "ShowDisplay",        .command.command2 = ShowDisplayTest,        .command_type = COMMAND_TYPE_2},
    {.name = "WriteDecrementDir",  .command.command0 = WriteDecrementDirTest,  .command_type = COMMAND_TYPE_0},
    {.name = "WriteIncrementDir",  .command.command0 = WriteIncrementDirTest,  .command_type = COMMAND_TYPE_0},
    {.name = "MoveDisplay",        .command.command0 = MoveDisplayTest,        .command_type = COMMAND_TYPE_0},
    {.name = "WriteCustomSymbols", .command.command0 = WriteCustomSymbolsTest, .command_type = COMMAND_TYPE_0},
    {.name = "CommonTest",         .command.command0 = TestsLCD1602,           .command_type = COMMAND_TYPE_0}
};

// Get UART Handle Type pointer
static UART_HandleTypeDef * GetUartHandler()
{
    return s_uart_handler;
}

// Set UART Handle Type pointer
static void SetUartHandler(UART_HandleTypeDef * uart_handler)
{
    s_uart_handler = uart_handler;
}

// Send a list of supported commands to show them on terminal related with UART channel
static HAL_StatusTypeDef ShowHelp()
{
    HAL_StatusTypeDef status = HAL_ERROR;
    char command_name[30];
    char commands_list[30*COMMANDS_COUNT];
    commands_list[0] = 0;
    UART_HandleTypeDef * uart_handle_type_def = GetUartHandler();

    if ((status = UartSendString(uart_handle_type_def, HELP, strlen(HELP), HAL_MAX_DELAY)) != HAL_OK)
    {
        return status;
    }

    for (uint8_t i = 0; i < COMMANDS_COUNT; i++)
    {
        sprintf(command_name, "%s\r\n", COMMANDS[i].name);
        strcat(commands_list, command_name);
    }

    if ((status = UartSendString(uart_handle_type_def, commands_list, strlen(commands_list), HAL_MAX_DELAY)) != HAL_OK)
    {
        return status;
    }

    return status;
}

// Read command
HAL_StatusTypeDef ReadCommand(uint8_t command[])
{
    return UartReceiveCommand(GetUartHandler(), command, MAX_COMMAND_LENGTH, HAL_MAX_DELAY);
}

// Process command
HAL_StatusTypeDef ProcessCommand(const char command[])
{
	UART_HandleTypeDef * uart_handler = GetUartHandler();
	HAL_StatusTypeDef status = HAL_ERROR;

	for (uint8_t i = 0; i < COMMANDS_COUNT; i++ )
    {
    	if (!strcmp(command, COMMANDS[i].name))
    	{
    		status = UartSendString(uart_handler, WAIT_FOR_COMMAND_TO_BE_FINISHED,
    				                strlen(WAIT_FOR_COMMAND_TO_BE_FINISHED), HAL_MAX_DELAY);
    		if (status != HAL_OK)
    		{
    		    return status;
    		}
    		switch (COMMANDS[i].command_type)
    		{
    		    case COMMAND_TYPE_0:
        		    COMMANDS[i].command.command0();
    		        break;
    		    case COMMAND_TYPE_1:
        			COMMANDS[i].command.command1(uart_handler);
        		    break;
    		    case COMMAND_TYPE_2:
        		    char comment[100];
        		    char message[100];
        		    COMMANDS[i].command.command2(comment, message);
    		        break;
    		    default:
    		        // Wrong command type
    		    	return UartSendString(uart_handler, WRONG_COMMAND_TYPE,
    		                              strlen(WRONG_COMMAND_TYPE), HAL_MAX_DELAY);
    		}

    		return UartSendString(uart_handler, SUCCEEDED, strlen(SUCCEEDED), HAL_MAX_DELAY);
    	}
    }

    return UartSendString(uart_handler, UNSUPPORTED_COMMAND, strlen(UNSUPPORTED_COMMAND), HAL_MAX_DELAY);
}

// Prepare I2C channel to communicate with LCD1602
uint8_t PrepareLCD1602Interface()
{
	return ShowLCD1602Interface(LCD1602_I2C);
}

// Prepare UART channel
HAL_StatusTypeDef PrepareUartChannel(UART_HandleTypeDef * uart_handler)
{
	HAL_StatusTypeDef status = HAL_ERROR;
    uint8_t attempts_count = 0;

    SetUartHandler(uart_handler);

    while ((status != HAL_OK) && attempts_count < MAX_ATTEMPTS_COUNT)
	{
        if ((status = UartReady(uart_handler)) == HAL_OK)
        {
        	status = ProcessCommand(SHOW_HELP_COMMAND);
        	if (status == HAL_OK)
        	{
        	    break;
        	}
        }

    	Lcd1602ScreenClear();
		Lcd1602SetCursor(0, 1);
        Lcd1602WriteString("Can't connect");
        Lcd1602SetCursor(1, 0);
        Lcd1602WriteString("to UART channel!");
        HAL_Delay(UART_TIMEOUT_SEC);
        attempts_count++;
	}

    if (status == HAL_OK)
    {
        Lcd1602ScreenClear();
    	Lcd1602SetCursor(0, 3);
        Lcd1602WriteString("Connected");
        Lcd1602SetCursor(1, 0);
        Lcd1602WriteString("to UART channel!");
        HAL_Delay(UART_TIMEOUT_SEC);
        Lcd1602ScreenClear();
    	Lcd1602SetCursor(0, 2);
        Lcd1602WriteString("Send commands");
        Lcd1602SetCursor(1, 0);
        Lcd1602WriteString("to UART channel!");
        HAL_Delay(UART_TIMEOUT_SEC);
    }

    return status;
}

// Repair UART channel
void RepairUartChannel(UART_HandleTypeDef * uart_handler)
{
    while (PrepareUartChannel(uart_handler) != HAL_OK)
    {
        HAL_Delay(UART_TIMEOUT_SEC);
    }
}
