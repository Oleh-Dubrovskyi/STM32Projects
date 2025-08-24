/*
 * lcd1602_tests.h
 *
 *  Created on: Aug 24, 2025
 *      Author: Oleh
 */

#ifndef INC_LCD1602_TESTS_LCD1602_TESTS_H_
#define INC_LCD1602_TESTS_LCD1602_TESTS_H_

// LCD1602 tests

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

// Test Prologue function
uint8_t PrologueTestsLCD1602(Lcd1602DataBusSize data_bus_size);

// Test Epiloge function
uint8_t EpilogeTestsLCD1602();

#endif /* INC_LCD1602_TESTS_LCD1602_TESTS_H_ */
