/**
  ***************************************************************************************
  * @file      : lcd1602.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to manage the LCD1602 display associated
  *            : with STM32F401RExx devices using 4-bit or 8-bit bus
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

#include "../Inc/lcd1602.h"

const uint8_t LCD1602_ROWS[] = {0x00, 0x40};
const GPIO_PinState LCD1602_DATA_REG = GPIO_PIN_SET;
const GPIO_PinState LCD1602_COMMAND_REG = GPIO_PIN_RESET;

// The default configuration of the data bus size is LCD1602_DATA_BUS_SIZE4 (4-bits mode)
Lcd1602DataBusSize g_lcd1602_data_bus_size = LCD1602_DATA_BUS_SIZE4;

// The default configuration of the Instruction/Data register selection pin
GpioItem g_lcd1602_gpio_rs = {GPIOB, GPIO_PIN_5};

// The default configuration of the Enable signal pin
GpioItem g_lcd1602_gpio_e = {GPIOB, GPIO_PIN_4};

// The default configuration of the lcd1602 data bus pins (for 4-bits mode)
GpioItem g_lcd1602_gpio_data_bus[] =
    {
        {GPIOC, GPIO_PIN_7},
        {GPIOB, GPIO_PIN_6},
        {GPIOA, GPIO_PIN_7},
        {GPIOA, GPIO_PIN_6},
        {NULL, 0},
        {NULL, 0},
        {NULL, 0},
        {NULL, 0}
    };

// Configure data bus and registers of the LCD1602
void Lcd1602Configure(Lcd1602DataBusSize data_bus_size,
		              GpioItem lcd1602_gpio_data_bus[],
					  GpioItem enable_signal,
					  GpioItem register_selection)
{
	Lcd1602SetDataBusSize(data_bus_size);
	Lcd1602ConfigureDataBus(lcd1602_gpio_data_bus);
	Lcd1602ConfigureE(enable_signal);
	Lcd1602ConfigureRS(register_selection);
}

// Configure data bus and registers of the LCD1602 for the 4-bits mode
void Lcd1602Configure4Bits(GpioItem lcd1602_gpio_data_bus[], GpioItem enable_signal, GpioItem register_selection)
{
    // Configure Data bus size
    g_lcd1602_data_bus_size = LCD1602_DATA_BUS_SIZE4;

    Lcd1602Configure(g_lcd1602_data_bus_size, lcd1602_gpio_data_bus, enable_signal, register_selection);

    Lcd1602Initialize();
}

// Configure data bus and registers of the LCD1602 for the 8-bits mode
void Lcd1602Configure8Bits(GpioItem lcd1602_gpio_data_bus[], GpioItem enable_signal, GpioItem register_selection)
{
	// Configure Data bus size
    g_lcd1602_data_bus_size = LCD1602_DATA_BUS_SIZE4;

    Lcd1602Configure(g_lcd1602_data_bus_size, lcd1602_gpio_data_bus, enable_signal, register_selection);

    Lcd1602Initialize();
}

// Initialize the Display
void Lcd1602Initialize()
{
	HAL_Delay(60);
	if (g_lcd1602_data_bus_size == LCD1602_DATA_BUS_SIZE4)
    {
        // 4-bits bus mode
		Lcd1602Write2NibblesToCommandRegister(LCD1602_BIT4_FIRST_INITIALIZATION_BYTE);
		Lcd1602Write2NibblesToCommandRegister(LCD1602_BIT4_SECOND_INITIALIZATION_BYTE);
		// Send the Function Set command with DL=0 flag (i.e. 4-bits), N=1 flag (i.e. 2R) and F=0 (i.e. 5x8 character font)
    	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_FUNCTION_SET | LCD1602_FLAG_N_2R);
    }
    else
    {
        // 8-bits bus mode
    	// Send the Function Set command with DL=1 flag (i.e. 8-bits), N=0 flag (i.e. 1R) and F=0 (i.e. 5x8 character font)
    	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_FUNCTION_SET | LCD1602_FLAG_DL_8D);
    	HAL_Delay(20);
    }

	HAL_Delay(1);
	// Common part of initialization
    // Switch Display on; cursor off; blink off
    Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH | LCD1602_FLAG_DISPLAY_ON);
    if (g_lcd1602_data_bus_size == LCD1602_DATA_BUS_SIZE8)
    {
    	// 8-bits bus mode
        // Send the Function Set command with DL=1 flag (i.e. 8-bits), N=1 flag (i.e. 2R) and F=0 (i.e. 5x8 character font)
        Lcd1602WriteByteToCommandRegister(LCD1602_CMD_FUNCTION_SET | LCD1602_FLAG_DL_8D | LCD1602_FLAG_N_2R);
        HAL_Delay(20);
    }
    // Set increment moving direction of cursor (cursor to increment automatically after writing a character; the display is not shifting)
    Lcd1602SetIncrementDirection();
	// Screen Clear; Set Address counter for DDRAM & CGRAM to 0
	Lcd1602ScreenClear();
	// Return Home
	Lcd1602SetCursor(0, 0);
}

// Set a data bus size
void Lcd1602SetDataBusSize(Lcd1602DataBusSize data_bus_size)
{
    g_lcd1602_data_bus_size = data_bus_size;
}

// Configure a data bus pins' set
void Lcd1602ConfigureDataBus(GpioItem lcd1602_gpio_data_bus[])
{
    for (uint8_t i = 0; i < g_lcd1602_data_bus_size; i++)
    {
        g_lcd1602_gpio_data_bus[i] = lcd1602_gpio_data_bus[i];
    }
}

// Configure Instruction/Data register selection pin
void Lcd1602ConfigureRS(GpioItem register_selection)
{
	g_lcd1602_gpio_rs.gpio_type = register_selection.gpio_type;
	g_lcd1602_gpio_rs.gpio_pin = register_selection.gpio_pin;
}

// Configure Enable signal pin
void Lcd1602ConfigureE(GpioItem enable_signal)
{
	g_lcd1602_gpio_e.gpio_type = enable_signal.gpio_type;
	g_lcd1602_gpio_e.gpio_pin = enable_signal.gpio_pin;
}

// Prepare a data bus and write
void Lcd1602SetDataBusAndWrite(uint8_t data)
{
    // Prepare data bus pins
	for (uint8_t i = 0; i < g_lcd1602_data_bus_size; i++)
	{
		HAL_GPIO_WritePin(g_lcd1602_gpio_data_bus[i].gpio_type,
				          g_lcd1602_gpio_data_bus[i].gpio_pin, (data >> i) & 0x01);
	}

    // Enable to write
	HAL_GPIO_WritePin(g_lcd1602_gpio_e.gpio_type, g_lcd1602_gpio_e.gpio_pin, GPIO_PIN_SET);
	HAL_Delay(1);
    HAL_GPIO_WritePin(g_lcd1602_gpio_e.gpio_type, g_lcd1602_gpio_e.gpio_pin, GPIO_PIN_RESET);
}

// Select instruction or data register to write
void Lcd1602SelectCommandDataRegister(GPIO_PinState command_data_register)
{
    HAL_GPIO_WritePin(g_lcd1602_gpio_rs.gpio_type, g_lcd1602_gpio_rs.gpio_pin, command_data_register);
}

// Write byte to the instruction or data register
void Lcd1602WriteByteToRegister(uint8_t data, GPIO_PinState command_data_register)
{
	Lcd1602SelectCommandDataRegister(command_data_register);

    if (g_lcd1602_data_bus_size == LCD1602_DATA_BUS_SIZE4)
    {
        // 4-bit mode
    	Lcd1602SetDataBusAndWrite(data >> 4);
    	Lcd1602SetDataBusAndWrite(data & 0x0F);
    }
    else
    {
        // 8-bit mode
    	Lcd1602SetDataBusAndWrite(data);
    }
}

// Write 2 Nibbles to the instruction with pause
void Lcd1602Write2NibblesToCommandRegister(uint8_t data)
{
	Lcd1602SelectCommandDataRegister(LCD1602_COMMAND_REG);

    Lcd1602SetDataBusAndWrite(data >> 4);
    HAL_Delay(5);
    Lcd1602SetDataBusAndWrite(data & 0x0F);
    HAL_Delay(1);
}

// Write byte to the instruction register
void Lcd1602WriteByteToCommandRegister(uint8_t command)
{
	Lcd1602WriteByteToRegister(command, LCD1602_COMMAND_REG);
}
// Write byte to the data register
void Lcd1602WriteByteToDataRegister(uint8_t data)
{
	Lcd1602WriteByteToRegister(data, LCD1602_DATA_REG);
}

// Screen Clear; Set Address counter for DDRAM & CGRAM to 0
void Lcd1602ScreenClear()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_SCREEN_CLEAR);
}

// Set DDRAM AD to 0; Set Cursor position to (0,0); Content of the DDRAM is not changed
void Lcd1602CursorReturn()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_CURSOR_RETURN);
}

// Set moving direction of cursor to left while moving
void Lcd1602MoveCursorToLeft()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_SHIFT);
}

// Set moving direction of cursor to right while moving
void Lcd1602MoveCursorToRight()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_SHIFT | LCD1602_FLAG_RIGHT_SHIFT);
}

// Set decrement cursor moving direction
void Lcd1602SetDecrementDirection()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_INPUT_SET);
}

// Set increment cursor moving direction
void Lcd1602SetIncrementDirection()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_INPUT_SET | LCD1602_FLAG_I_D_INCREMENT_MODE);
}

// Scroll Display to left
void Lcd1602DisplayToLeft()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_SHIFT | LCD1602_FLAG_DISPLAY_SHIFT);
}

// Scroll Display to right
void Lcd1602DisplayToRight()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_SHIFT | LCD1602_FLAG_DISPLAY_SHIFT | LCD1602_FLAG_RIGHT_SHIFT);
}

// Show Display
void Lcd1602ShowDisplay()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH | LCD1602_FLAG_DISPLAY_ON);
}

// Hide Display
void Lcd1602HideDisplay()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH);
}

// Show cursor
void Lcd1602ShowCursor()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH | LCD1602_FLAG_DISPLAY_ON | LCD1602_FLAG_CURSOR_ON);
}

// Show blink cursor
void Lcd1602ShowBlinkCursor()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH | LCD1602_FLAG_DISPLAY_ON
			                        | LCD1602_FLAG_CURSOR_ON | LCD1602_FLAG_CURSOR_BLINK_ON);
}

// Hide cursor
void Lcd1602HideCursor()
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DISPLAY_SWITCH | LCD1602_FLAG_DISPLAY_ON);
}

//LCD1602_FLAG_CURSOR_BLINK_ON
// Switch cursor to blink on
void Lcd1602BlinkCursorOn()
{
	Lcd1602ShowBlinkCursor();
}
// Switch cursor to blink off
void Lcd1602BlinkCursorOff()
{
	Lcd1602ShowCursor();
}
// Set cursor position (0,0) - (1,15)
void Lcd1602SetCursor(uint8_t row, uint8_t col)
{
	if (row > 1)
	{
        row = 1;
    }
	if (col > 15)
	{
        col = 15;
    }

	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_DDRAM_AD_SET | LCD1602_ROWS[row] | col);
}

// Write string from cursor point
void Lcd1602WriteString(char * string)
{
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		Lcd1602WriteByteToDataRegister(string[i]);
	}
}

// Write number from cursor point
void Lcd1602WriteNumber(int number)
{
	char str_number[12];

	sprintf(str_number, "%d", number);
	Lcd1602WriteString(str_number);
}

// Write float from cursor point
void Lcd1602WriteFloat(float value, char * format)
{
    char str_float[12];

    sprintf(str_float, format, value);
    Lcd1602WriteString(str_float);
}

// Create custom symbol
void Lcd1602CreateCustomSymbol(uint8_t position, char * pattern)
{
	Lcd1602WriteByteToCommandRegister(LCD1602_CMD_CGRAM_AD_SET + position*8);
	for (int i = 0; i < 8; i++)
	{
		Lcd1602WriteByteToDataRegister(pattern[i]);
	}
}
