/**
  ************************************************************************************
  * @file      : lcd1602_i2c_tests.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for lcd1602_i2c_tests.c file.
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

#ifndef INC_LCD1602_I2C_TESTS_LCD1602_TESTS_H
#define INC_LCD1602_I2C_TESTS_LCD1602_TESTS_H

// LCD1602/I2C tests

// Write string test
void WriteStringTest(char comment[], char message[]);

// Clear screen test
void ClearScreenTest(char comment[], char message[]);

// Show cursor test
void ShowCursorTest(char comment[], char message[]);

// Return Cursor test
void ReturnCursorTest(char comment[], char message[]);

// Hide Cursor test
void HideCursorTest(char comment[], char message[]);

// Hide Display test
void HideDisplayTest(char comment[], char message[]);

// Show Display test
void ShowDisplayTest(char comment[], char message[]);

// Blink Cursor On test
void BlinkCursorOnTest(char comment[], char message[]);

// Blink Cursor Off test
void BlinkCursorOffTest(char comment[], char message[]);

// Move Cursor to right test
void MoveCursorToRightTest(char comment[], char message[]);

// Move Cursor to left test
void MoveCursorToLeftTest(char comment[], char message[]);

// Set Cursor Position test
void SetCursorPositionTest(char comment[], char message[]);

// Write number test
void WriteNumberTest(char comment[], char message[]);

// Write float test
void WriteFloatTest(char comment[], char message[]);

// Write Decrement Direction test
void WriteDecrementDirTest();

// Write Increment Direction test
void WriteIncrementDirTest();

// Move Display test
void MoveDisplayTest();

// Write custom symbols test
void WriteCustomSymbolsTest();

// Common LCD1602 test (21 steps)
void TestsLCD1602();

// Show LCD1602 interface
uint8_t ShowLCD1602Interface(Lcd1602InterfaceType lcd1602_interface_type);

// Test Prologue function
uint8_t PrologueTestsLCD1602(Lcd1602InterfaceType lcd1602_interface_type, char first_line[], char second_line[]);

// Test Epiloge function
uint8_t EpilogeTestsLCD1602();

#endif // INC_LCD1602_I2C_TESTS_LCD1602_TESTS_H
