/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd1602.h"
#include "lcd1602_custom.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ConfigureLCD1602(Lcd1602DataBusSize data_bus_size,
		              GpioItem lcd1602_gpio_data_bus[],
					  GpioItem enable_signal,
					  GpioItem register_selection)
{
	Lcd1602SetDataBusSize(data_bus_size);
	Lcd1602ConfigureDataBus(lcd1602_gpio_data_bus);
	Lcd1602ConfigureE(enable_signal);
	Lcd1602ConfigureRS(register_selection);
}

// Tests

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

void ConfigureLCD1602_4Bits()
{
	  // Configure Data bus size
	  Lcd1602DataBusSize data_bus_size = LCD1602_DATA_BUS_SIZE4;

	  // Configure Data bus pins
	  GpioItem lcd1602_gpio_data_bus[] =
	  {
	      {GPIOC, GPIO_PIN_7},  // D4
	      {GPIOB, GPIO_PIN_6},  // D5
	      {GPIOA, GPIO_PIN_7},  // D6
	      {GPIOA, GPIO_PIN_6},  // D7
	      {NULL, 0},
	      {NULL, 0},
	      {NULL, 0},
	      {NULL, 0}
	  };

	  // Configure Enable signal pin
	  GpioItem enable_signal = {GPIOB, GPIO_PIN_4};

	  // Configure Register selection pin
	  GpioItem register_selection = {GPIOB, GPIO_PIN_5};

	  ConfigureLCD1602(data_bus_size, lcd1602_gpio_data_bus, enable_signal, register_selection);

	  Lcd1602Initialize();
}

void ConfigureLCD1602_8Bits()
{
	  // Configure Data bus size
	  Lcd1602DataBusSize data_bus_size = LCD1602_DATA_BUS_SIZE8;

	  // Configure Data bus pins
	  GpioItem lcd1602_gpio_data_bus[] =
	  {
          {GPIOA, GPIO_PIN_1},  // D0
		  {GPIOA, GPIO_PIN_4},  // D1
		  {GPIOB, GPIO_PIN_0},  // D2
		  {GPIOC, GPIO_PIN_1},  // D3
		  {GPIOC, GPIO_PIN_7},  // D4
	      {GPIOB, GPIO_PIN_6},  // D5
	      {GPIOA, GPIO_PIN_7},  // D6
	      {GPIOA, GPIO_PIN_6}   // D7
	  };

	  // Configure Enable signal pin
	  GpioItem enable_signal = {GPIOB, GPIO_PIN_4};

	  // Configure Register selection pin
	  GpioItem register_selection = {GPIOB, GPIO_PIN_5};

	  ConfigureLCD1602(data_bus_size, lcd1602_gpio_data_bus, enable_signal, register_selection);

	  Lcd1602Initialize();
}

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
        ConfigureLCD1602_8Bits();
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
        ConfigureLCD1602_4Bits();
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

// Test Epilog function
uint8_t EpilogTestsLCD1602()
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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  for (uint8_t i = 0; i < 2; i++)
  {
      // LCD1602 - 4-bit tests
      if (PrologueTestsLCD1602(LCD1602_DATA_BUS_SIZE4) == 1)
      {
          HAL_Delay(2000);
          TestsLCD1602();
          EpilogTestsLCD1602();
      }

      // LCD1602 - 8-bit tests
      if (PrologueTestsLCD1602(LCD1602_DATA_BUS_SIZE8) == 1)
      {
          HAL_Delay(2000);
          TestsLCD1602();
          EpilogTestsLCD1602();
      }
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_4|LD2_Pin|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA4 LD2_Pin PA6
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|LD2_Pin|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
