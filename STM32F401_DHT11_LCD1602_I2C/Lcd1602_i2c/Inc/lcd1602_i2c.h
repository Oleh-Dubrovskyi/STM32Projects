/**
  ************************************************************************************
  * @file      : lcd1602_i2c.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for lcd1602_i2c.c file.
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

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#ifndef INC_LCD1602_I2C_H
#define INC_LCD1602_I2C_H

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

// I2C Address for the PCF8574T converter
#define PCF8574T_ADDRESS 0x4E //  (0x27 << 1) = 0x4E
// PCF8574T converter RS pin (P0): Register Select
#define PCF8574T_RS_COMMAND 0x00
#define PCF8574T_RS_DATA 0x01
// PCF8574T converter RW pin (P1): Read/Write
#define PCF8574T_RW 0x02
// PCF8574T converter E pin (P2): Enable to transmit
#define PCF8574T_E 0x04
// PCF8574T converter K pin (P3): Display Backlight
#define PCF8574T_K 0x08

// Interface types (i2c/4-bit/8-bit)
typedef enum Lcd1602InterfaceType_
{
	LCD1602_I2C = 2,
	LCD1602_DATA_BUS_SIZE4 = 4,
	LCD1602_DATA_BUS_SIZE8 = 8
} Lcd1602InterfaceType;

typedef enum Lcd1602InterfaceType_ Lcd1602DataBusSize;

// GPIO pin description
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} GpioItem;

extern const uint8_t LCD1602_ROWS[];
extern const GPIO_PinState LCD1602_DATA_REG;
extern const GPIO_PinState LCD1602_COMMAND_REG;
// Lcd1602 Interface Type
extern Lcd1602InterfaceType g_lcd1602_interface_type;
// Data bus pins array
extern GpioItem g_lcd1602_gpio_data_bus[];
// Instruction/Data register selection pin
extern GpioItem g_lcd1602_gpio_rs;
// Enable signal pin
extern GpioItem g_lcd1602_gpio_e;
// Undefined GPIO
extern const GpioItem UNDEFINED_GPIO;

// Get interface type to communicate with LCD1602 Display
Lcd1602InterfaceType Lcd1602GetInterfaceType();
// Set interface type to communicate with LCD1602 Display
void Lcd1602SetInterfaceType(Lcd1602InterfaceType interface_type);
// Configure interface type, data bus and registers of the LCD1602
void Lcd1602Configure(Lcd1602InterfaceType interface_type,
		              GpioItem lcd1602_gpio_data_bus[],
					  GpioItem enable_signal,
					  GpioItem register_selection);
// Configure data bus of the LCD1602/PCF8574T for the i2c mode
void Lcd1602ConfigureI2C(GpioItem lcd1602_gpio_data_bus[]);
// Configure data bus and registers of the LCD1602 for the 4-bits mode
void Lcd1602Configure4Bits(GpioItem lcd1602_gpio_data_bus[], GpioItem enable_signal, GpioItem register_selection);
// Configure data bus and registers of the LCD1602 for the 8-bits mode
void Lcd1602Configure8Bits(GpioItem lcd1602_gpio_data_bus[], GpioItem enable_signal, GpioItem register_selection);
// Initialize the Display
void Lcd1602Initialize();
// Initialize the Display 1602 through I2C converter PCF8574T
void Lcd1602InitializeThrougPCF8574T();
// Switch Display Back Light On/Off through I2C converter PCF8574T
void Lcd1602SwitchDisplayOnOffThrougPCF8574T(uint8_t on_off);
// Send byte to LCD1602 through I2C converter PCF8574T
void Lcd1602SendByteThrougPCF8574T(uint8_t _data);
// Send Enable Pulse to LCD1602 through I2C converter PCF8574T
void Lcd1602EnableToTransmitThroughPCF8574T(uint8_t byte);
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
// Write 2 Nibbles to the instruction register with pause
void Lcd1602Write2NibblesToCommandRegister(uint8_t data);
// Send 2 Nibbles to the instruction register through the converter PCF8574T with pause
void Lcd1602Send2NibblesThroughPCF8574T(uint8_t data, uint8_t mode);
// Send command byte through the converter PCF8574T
void Lcd1602SendCommandThroughPCF8574T(uint8_t command);
// Send data byte through the converter PCF8574T
void Lcd1602SendDataThroughPCF8574T(uint8_t data);
// Send 2 Nibbles with pause to the instruction register through the converter PCF8574T with pause
void Lcd1602Send2PausedNibblesThroughPCF8574T(uint8_t data);
// Write byte to the instruction register
void Lcd1602WriteByteToCommandRegister(uint8_t command);
// Write byte to the data register
void Lcd1602WriteByteToDataRegister(uint8_t data);
// Send command to LCD1602 through current channel
void Lcd1602SendCommand(uint8_t command);
// Send data byte to LCD1602 through current channel
void Lcd1602SendDataByte(uint8_t data);
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

#endif // INC_LCD1602_I2C_H
