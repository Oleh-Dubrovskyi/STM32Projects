/*
 * lcd1602_tests.c
 *
 *  Created on: Aug 24, 2025
 *      Author: Oleh
 */

#include "lcd1602/lcd1602.h"
#include "lcd1602/lcd1602_custom.h"

// LCD1602 Tests

// Write string test
void WriteStringTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Write string");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);
    strcpy(message,  "LCD1602 - test");
    Lcd1602SetCursor(1, 1);
    Lcd1602WriteString(message);
    HAL_Delay(5000);
}

// Clear screen test
void ClearScreenTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Clear screen");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);
    HAL_Delay(2000);
    Lcd1602ScreenClear();
    HAL_Delay(5000);
}

// Show cursor test
void ShowCursorTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Show cursor");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);
    Lcd1602SetCursor(1, 8);
    Lcd1602ShowCursor();
    HAL_Delay(5000);   // Cursor is visible
}

// Return Cursor test
void ReturnCursorTest(char comment[], char message[])
{
    Lcd1602ScreenClear();  // Cursor is visible
    strcpy(comment, "Return cursor");
    Lcd1602SetCursor(1, 1);
    Lcd1602WriteString(comment);
    Lcd1602CursorReturn();
    HAL_Delay(5000);
}

// Hide Cursor test
void HideCursorTest(char comment[], char message[])
{
	Lcd1602ScreenClear();  // Cursor is visible
    strcpy(comment, "Hide cursor");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);
    Lcd1602HideCursor();
    HAL_Delay(5000);  // Cursor is not visible
}

// Hide Display test
void HideDisplayTest(char comment[], char message[])
{
	Lcd1602ScreenClear();  // Cursor is visible
	strcpy(comment, "Hide display");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);
    HAL_Delay(2000);
    Lcd1602HideDisplay();
    HAL_Delay(5000);  // Cursor is not visible
}

// Show Display test
void ShowDisplayTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Show display");
    Lcd1602SetCursor(0, 1);
    Lcd1602WriteString(comment);  // Message and cursor are not visible
    Lcd1602ShowDisplay();
    HAL_Delay(5000);  // Message is visible, Cursor is not visible
}

// Blink Cursor On test
void BlinkCursorOnTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Blink cursor On");
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(comment);  // Cursor is not visible
    Lcd1602SetCursor(1, 8);
    Lcd1602ShowCursor();
    Lcd1602BlinkCursorOn();  // Cursor is visible
    HAL_Delay(5000);  // Cursor is blinking
}

// Blink Cursor Off test
void BlinkCursorOffTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Blink cursor Off");
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(comment);
    Lcd1602SetCursor(1, 8);
    Lcd1602ShowCursor();
    HAL_Delay(1000);
    Lcd1602BlinkCursorOff();
    HAL_Delay(5000);
}

// Move Cursor to right test
void MoveCursorToRightTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    Lcd1602HideCursor();
	strcpy(comment, "Cursor to right");
	Lcd1602SetCursor(0, 0);
	Lcd1602WriteString(comment);
	Lcd1602SetCursor(1, 8);
	Lcd1602ShowCursor();
	HAL_Delay(1000);
	Lcd1602MoveCursorToRight();
	HAL_Delay(500);
	Lcd1602MoveCursorToRight();
	HAL_Delay(2000);
}

// Move Cursor to left test
void MoveCursorToLeftTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    Lcd1602HideCursor();
    strcpy(comment, "Cursor to left");
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(comment);
    Lcd1602SetCursor(1, 8);
    Lcd1602ShowCursor();
    HAL_Delay(1000);
    Lcd1602MoveCursorToLeft();
    HAL_Delay(500);
    Lcd1602MoveCursorToLeft();
    HAL_Delay(2000);
}

// Set Cursor Position test
void SetCursorPositionTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    strcpy(comment, "Setting cursor >");
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(comment);

    //Lcd1602SetCursor(0, 0);
	for (uint8_t row = 0; row < 2; row++)
    {
        for (uint8_t col = 0; col < 16; col++)
        {
  	      Lcd1602SetCursor(row, col);
  	      HAL_Delay(200);
        }
    }

    strcpy(comment, "Setting cursor <");
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(comment);

    Lcd1602SetCursor(1, 15);
	for (uint8_t row = 0; row < 2; row++)
    {
        for (uint8_t col = 0; col < 16; col++)
        {
  	      Lcd1602SetCursor(1 - row, 15 - col);
          HAL_Delay(200);
        }
    }
    HAL_Delay(2000);
}

// Write number test
void WriteNumberTest(char comment[], char message[])
{
    Lcd1602ScreenClear();
    Lcd1602HideCursor();
    strcpy(comment, "Write Number");
    Lcd1602SetCursor(0, 2);
    Lcd1602WriteString(comment);

    for (int i = 0; i < 15 ; i++)
    {
        Lcd1602SetCursor(1, 7);
        Lcd1602WriteNumber(i);
        HAL_Delay (500);
    }
}

// Write float test
void WriteFloatTest(char comment[], char message[])
{
    float start = 25.25;

    Lcd1602ScreenClear();
    Lcd1602HideCursor();
    strcpy(comment, "Write Float");
    Lcd1602SetCursor(0, 3);
    Lcd1602WriteString(comment);

    for (int i = 0; i < 10; i++)
    {
	      Lcd1602SetCursor(1, 5);
	      float result = start + (float)i/100.;
	      Lcd1602WriteFloat(result, "%2.2f");
	      HAL_Delay (500);
    }
}

// Write Decrement Direction test
void WriteDecrementDirTest()
{
    Lcd1602ScreenClear();
    Lcd1602HideCursor();
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString("Decrement direct");
    Lcd1602SetDecrementDirection();
    Lcd1602SetCursor(1, 15);
    Lcd1602WriteString("Decrement direct");
    HAL_Delay(5000);
}

// Write Increment Direction test
void WriteIncrementDirTest()
{
    Lcd1602ScreenClear();
    Lcd1602SetIncrementDirection();
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString("Increment direct");
    Lcd1602SetCursor(1, 0);
    Lcd1602WriteString("Increment direct");
    Lcd1602SetIncrementDirection();
    HAL_Delay(5000);
}

// Move Display test
void MoveDisplayTest()
{
    Lcd1602ScreenClear();
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString("Move Display < < < < < < <");
    HAL_Delay(1000);
	for (uint8_t i = 0; i < 16; i++)
    {
        Lcd1602DisplayToLeft();
        HAL_Delay(500);
    }

	HAL_Delay(1000);

	for (uint8_t i = 0; i < 16; i++)
    {
        Lcd1602DisplayToRight();
        HAL_Delay(500);
    }

	HAL_Delay(1000);
}

// Write custom symbols test
void WriteCustomSymbolsTest()
{
    Lcd1602ScreenClear();
    Lcd1602SetCursor(0, 2);
    Lcd1602WriteString("Custom symbol");
    //HAL_Delay(1000);
	Lcd1602CreateCustomSymbol(BIG_BE, PATTERN_BIG_BE);
	Lcd1602CreateCustomSymbol(LITTLE_BE, PATTERN_LITTLE_BE);
	Lcd1602CreateCustomSymbol(BIG_GE, PATTERN_BIG_GE);
	Lcd1602CreateCustomSymbol(LITTLE_GE, PATTERN_LITTLE_GE);
	HAL_Delay(100);
	Lcd1602SetCursor(1, 8);
	Lcd1602WriteByteToRegister(BIG_BE, LCD1602_DATA_REG);
	HAL_Delay(5000);
	Lcd1602ScreenClear();
    Lcd1602SetCursor(0, 2);
    Lcd1602WriteString("Custom symbols");
	char test_string[] = {BIG_BE, LITTLE_BE, BIG_GE, LITTLE_GE, 0};
	Lcd1602SetCursor(1, 6);
	Lcd1602WriteString(test_string);
	HAL_Delay(5000);
}

// Common LCD1602 test (21 steps)
void TestsLCD1602()
{
	  char comment[100];
	  char message[100];

	  // 1. Write string test
	  WriteStringTest(comment, message);

      // 2. Write Number test
	  WriteNumberTest(comment, message);

      // 3. Write Float test
	  WriteFloatTest(comment, message);

      // 4. Write Custom Symbols test
	  WriteCustomSymbolsTest();

	  // 5. Clear screen
	  ClearScreenTest(comment, message);

	  // 6. Show cursor
	  ShowCursorTest(comment, message);

	  // 7. Return cursor
	  ReturnCursorTest(comment, message);

	  // 8. Hide cursor
	  HideCursorTest(comment, message);

	  // 9. Show cursor
	  ShowCursorTest(comment, message);

	  // 10. Hide display
	  HideDisplayTest(comment, message);

	  // 11. Show display
	  ShowDisplayTest(comment, message);

	  // 12. Blink cursor On
	  BlinkCursorOnTest(comment, message);

	  // 13. Blink cursor Off
	  BlinkCursorOffTest(comment, message);

      // 14. Move Cursor to right
	  MoveCursorToRightTest(comment, message);

      // 15. Move Cursor to left
	  MoveCursorToLeftTest(comment, message);

      // 16. Move Cursor to right
	  MoveCursorToRightTest(comment, message);

      // 17. Move Cursor to left
	  MoveCursorToLeftTest(comment, message);

	  // 18. Set Cursor position
	  SetCursorPositionTest(comment, message);

	  // 19. Write Decrement Direction test
	  WriteDecrementDirTest();

      // 20. Write Increment Direction test
	  WriteIncrementDirTest();

	  // 21. DisplayToLeftTest
	  MoveDisplayTest();
}

// Test Prologue function
uint8_t PrologueTestsLCD1602(Lcd1602DataBusSize data_bus_size)
{
    // Prolog for lcd1602 testing
	uint8_t result = 0;
	if (data_bus_size == LCD1602_DATA_BUS_SIZE8)
	{
		// 8-bit communication mode
		Lcd1602Configure8Bits();
        Lcd1602ScreenClear();
        Lcd1602SetCursor(0, 4);
        Lcd1602WriteString("LCD-1602");
        Lcd1602SetCursor(1, 0);
        Lcd1602WriteString("Start 8-bit test");
        HAL_Delay(2000);
        result = 1;
	}
	else if (data_bus_size == LCD1602_DATA_BUS_SIZE4)
	{
		// 4-bit communication mode
        Lcd1602Configure4Bits();
        Lcd1602ScreenClear();
        Lcd1602SetCursor(0, 4);
        Lcd1602WriteString("LCD-1602");
        Lcd1602SetCursor(1, 0);
        Lcd1602WriteString("Start 4-bit test");
		result = 1;
	}
	else
	{
		// Wrong/unsupported data_bus_size value.
		return result;
	}

    return result;
}

// Test Epiloge function
uint8_t EpilogeTestsLCD1602()
{
    // Epilog for lcd1602 testing
	if (g_lcd1602_data_bus_size == LCD1602_DATA_BUS_SIZE4)
	{
		// 4-bit communication mode epilog
        Lcd1602ScreenClear();
        Lcd1602SetCursor(0, 4);
        Lcd1602WriteString("LCD-1602");
        Lcd1602SetCursor(1, 1);
        Lcd1602WriteString("End 4-bit test");
        HAL_Delay(2000);
		return 1;
	}
	else if (g_lcd1602_data_bus_size == LCD1602_DATA_BUS_SIZE8)
	{
		// 8-bit communication mode epilog
        Lcd1602ScreenClear();
        Lcd1602SetCursor(0, 4);
        Lcd1602WriteString("LCD-1602");
        Lcd1602SetCursor(1, 1);
        Lcd1602WriteString("End 8-bit test");
        HAL_Delay(2000);
        return 1;
	}
	else
	{
		// Wrong/unsupported state of the g_lcd1602_data_bus_size value
		return 0;
	}

    return 0;
}
