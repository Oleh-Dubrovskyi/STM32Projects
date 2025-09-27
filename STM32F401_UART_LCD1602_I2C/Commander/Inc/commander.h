/**
  ************************************************************************************
  * @file      : commander.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for commander.c file.
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

#ifndef COMMANDER_H
#define COMMANDER_H

#include "stm32f4xx_hal.h"

#define COMMANDS_COUNT 20
#define MAX_COMMAND_LENGTH 30
#define MAX_ATTEMPTS_COUNT 250

typedef void (* TestCommand0)();
typedef HAL_StatusTypeDef (* TestCommand1)();
typedef void (* TestCommand2)(char comment[], char message[]);
typedef union
{
    TestCommand0 command0;
    TestCommand1 command1;
    TestCommand2 command2;
} TestCommand;

typedef enum
{
    COMMAND_TYPE_0,
    COMMAND_TYPE_1,
    COMMAND_TYPE_2
} CommandType;

typedef struct CommandStruct
{
    char name[20];
	TestCommand command;
    CommandType command_type;
} Command;

// Commands list
extern const Command COMMANDS[COMMANDS_COUNT];

// Read command
HAL_StatusTypeDef ReadCommand(uint8_t command[]);

// Process command
HAL_StatusTypeDef ProcessCommand(const char command[]);

// Prepare I2C channel to communicate with LCD1602
uint8_t PrepareLCD1602Interface();

// Prepare UART channel
HAL_StatusTypeDef PrepareUartChannel(UART_HandleTypeDef * uart_handler);

// Repair UART channel
void RepairUartChannel(UART_HandleTypeDef * uart_handler);

#endif // COMMANDER_H
