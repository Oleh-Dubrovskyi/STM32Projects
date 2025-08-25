/**
  ************************************************************************************
  * @file      : lcd1602.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for lcd1602.c file.
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

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"

// INSTRUCTIONS SET
#define LCD1602_CMD_SCREEN_CLEAR 0x01
#define LCD1602_CMD_CURSOR_RETURN 0x02
#define LCD1602_CMD_INPUT_SET 0x04
#define LCD1602_CMD_DISPLAY_SWITCH 0x08
#define LCD1602_CMD_SHIFT 0x10
#define LCD1602_CMD_FUNCTION_SET 0x20
#define LCD1602_CMD_CGRAM_AD_SET 0x40
#define LCD1602_CMD_DDRAM_AD_SET 0x80

// INSTRUCTIONS FLAGS SET
#define LCD1602_FLAG_CURSOR_BLINK_ON 0x01
#define LCD1602_FLAG_SHIFT 0x01
#define LCD1602_FLAG_I_D_INCREMENT_MODE 0x02
#define LCD1602_FLAG_CURSOR_SHIFT 0x02
#define LCD1602_FLAG_CURSOR_ON 0x02
#define LCD1602_FLAG_RIGHT_SHIFT 0x04
#define LCD1602_FLAG_DISPLAY_ON 0x04
#define LCD1602_FLAG_DISPLAY_SHIFT 0x08
#define LCD1602_FLAG_DL_8D 0x10
#define LCD1602_FLAG_N_2R 0x08
#define LCD1602_FLAG_F_5X10 0x04
#define LCD1602_FLAG_BF_EXECUTE_INTERNAL_FUNCTION 0x80

// LCD1602 Initialization bytes for the 4-bit data bus mode
#define LCD1602_BIT4_FIRST_INITIALIZATION_BYTE 0x33
#define LCD1602_BIT4_SECOND_INITIALIZATION_BYTE 0x32
#define LCD1602_BIT4_THIRD_INITIALIZATION_BYTE  (LCD1602_CMD_FUNCTION_SET | LCD1602_FLAG_N_2R)


// Interface types (4-bit/8-bit)
typedef enum
{
	LCD1602_DATA_BUS_SIZE4 = 4,
	LCD1602_DATA_BUS_SIZE8 = 8
} Lcd1602DataBusSize;

// GPIO pin description
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} GpioItem;

extern const uint8_t LCD1602_MAX_ROW;
extern const uint8_t LCD1602_MAX_COL;
extern const uint8_t LCD1602_ROWS[];
extern const GPIO_PinState LCD1602_DATA_REG;
extern const GPIO_PinState LCD1602_COMMAND_REG;
// Data bus size
extern Lcd1602DataBusSize g_lcd1602_data_bus_size;
// Data bus pins array
extern GpioItem g_lcd1602_gpio_data_bus[];
// Instruction/Data register selection pin
extern GpioItem g_lcd1602_gpio_rs;
// Enable signal pin
extern GpioItem g_lcd1602_gpio_e;

// Configure data bus and registers of the LCD1602
void Lcd1602Configure(Lcd1602DataBusSize data_bus_size,
		              GpioItem lcd1602_gpio_data_bus[],
					  GpioItem enable_signal,
					  GpioItem register_selection);

// Configure data bus and registers of the LCD1602 for the 4-bits mode
void Lcd1602Configure4Bits();

// Configure data bus and registers of the LCD1602 for the 8-bits mode
void Lcd1602Configure8Bits();

// Initialize the Display
void Lcd1602Initialize();

// Set a data bus size (4/8)
void Lcd1602SetDataBusSize(Lcd1602DataBusSize data_bus_size);
// Configure a data bus pins' set
void Lcd1602ConfigureDataBus(GpioItem lcd1602_gpio_data_bus[]);
// Configure Instruction/Data register selection pin
void Lcd1602ConfigureRS(GpioItem register_selection);
// Configure Enable signal pin
void Lcd1602ConfigureE(GpioItem enable_signal);
// Prepare a data bus and write
void Lcd1602SetDataBusAndWrite(uint8_t data);
// Select instruction or data register to write
void Lcd1602SelectCommandDataRegister(GPIO_PinState command_data_register);
// Write byte to the instruction or data register
void Lcd1602WriteByteToRegister(uint8_t data, GPIO_PinState command_data_register);
// Write 2 Nibbles to the instruction with pause
void Lcd1602Write2NibblesToCommandRegister(uint8_t data);
// Write byte to the instruction register
void Lcd1602WriteByteToCommandRegister(uint8_t command);
// Write byte to the data register
void Lcd1602WriteByteToDataRegister(uint8_t data);

// Screen Clear; Set Address counter for DDRAM & CGRAM to 0
void Lcd1602ScreenClear();
// Set DDRAM AD to 0; Set Cursor position to (0,0); Content Changeless
void Lcd1602CursorReturn();
// Set moving direction of cursor to left while moving
void Lcd1602MoveCursorToLeft();
// Set moving direction of cursor to right while moving
void Lcd1602MoveCursorToRight();
// Set decrement cursor moving direction
void Lcd1602SetDecrementDirection();
// Set increment cursor moving direction
void Lcd1602SetIncrementDirection();
// Scroll Display to left
void Lcd1602DisplayToLeft();
// Scroll Display to right
void Lcd1602DisplayToRight();
// Show Display
void Lcd1602ShowDisplay();
// Hide Display
void Lcd1602HideDisplay();
// Show cursor
void Lcd1602ShowCursor();
// Show blink cursor
void Lcd1602ShowBlinkCursor();
// Hide cursor
void Lcd1602HideCursor();
// Switch cursor to blink on
void Lcd1602BlinkCursorOn();
// Switch cursor to blink off
void Lcd1602BlinkCursorOff();
// Set cursor position (0,0) - (1,15)
void Lcd1602SetCursor(uint8_t row, uint8_t col);

// Write string from cursor point
void Lcd1602WriteString(char * string);
// Write number from cursor point
void Lcd1602WriteNumber(int number);
// Write float from cursor point
void Lcd1602WriteFloat(float value, char * format);

// Create custom symbol
void Lcd1602CreateCustomSymbol(uint8_t position, char * pattern);

#endif /* INC_LCD1602_H_ */
