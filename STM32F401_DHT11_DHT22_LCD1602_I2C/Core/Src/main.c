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
#include <stdio.h>
#include <string.h>
#include "../../DelayMicro/Inc/delay_micro.h"
#include "../../Dht/Inc/Dht.h"
#include "../../Lcd1602_i2c/Inc/lcd1602_i2c.h"
#include "stm32f4xx_hal.h"
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

/* USER CODE BEGIN PV */

static const uint8_t DHT_SENSORS_COUNT = 2;
static const uint8_t DHT11_SENSOR_IDX = 0;
static const uint8_t DHT22_SENSOR_IDX = 1;
static const uint32_t SENSORS_POLLING_PERIOD = 1000;

I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ShowDHTData(char * sensor_type, uint8_t temp_sign, float temperature, float humidity)
{
	char temperature_str[20];
    char humidity_str[20];

    sprintf(temperature_str, "%s Tc = %s%2.1Lf", sensor_type, (temp_sign ? "-":"+"), (long double)temperature);
    sprintf(humidity_str, "%s Rh = %2.1Lf%%", sensor_type, (long double)humidity);

    Lcd1602ScreenClear();
    Lcd1602SetCursor(0, 0);
    Lcd1602WriteString(temperature_str);
    Lcd1602SetCursor(1, 0);
    Lcd1602WriteString(humidity_str);
}

void ShowMessage(char * message1, char * message2, uint8_t pos1, uint8_t pos2)
{
    Lcd1602ScreenClear();
    Lcd1602SetCursor(0, pos1);
    Lcd1602WriteString(message1);
    Lcd1602SetCursor(1, pos2);
    Lcd1602WriteString(message2);
}

void ShowUnsupportedSensor()
{
    char message1[20];
    char message2[20];
	strcpy(message1, "*** Unsupported");
    strcpy(message2, "*** sensor");
    ShowMessage(message1, message2, 0, 3);
}

uint8_t SwitchSensorIndex(uint8_t dht_sensor_idx)
{
    return (dht_sensor_idx == DHT22_SENSOR_IDX) ? DHT11_SENSOR_IDX : DHT22_SENSOR_IDX;
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
  // Initialize TIM2 to use for micro-delays
  TIM2MicrosecondsDelayInit();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
    char message1[100];
    char message2[100];

    // DHT sensor descriptions' array
    DHTSensor dht_sensors[DHT_SENSORS_COUNT];

    // Configure DHT11 sensor
    DhtConfigureSensor(&dht_sensors[DHT11_SENSOR_IDX], DHT11, (DHTGpioDataLine){GPIOA, GPIO_PIN_0});

    // Configure DHT22 sensor
    DhtConfigureSensor(&dht_sensors[DHT22_SENSOR_IDX], DHT22, (DHTGpioDataLine){GPIOA, GPIO_PIN_1});

    // Set LCD1602 Interface type to I2C
    Lcd1602SetInterfaceType(LCD1602_I2C);

    // Configure LCD1602 data bus for I2C communication mode
	Lcd1602ConfigureI2C(
        (GpioItem[])
        {
            (GpioItem){GPIOB, GPIO_PIN_8},  // SCL
            (GpioItem){GPIOB, GPIO_PIN_9},  // SDA
            (GpioItem)UNDEFINED_GPIO,
            (GpioItem)UNDEFINED_GPIO,
            (GpioItem)UNDEFINED_GPIO,
            (GpioItem)UNDEFINED_GPIO,
            (GpioItem)UNDEFINED_GPIO,
            (GpioItem)UNDEFINED_GPIO
        });

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    uint8_t dht_sensor_idx = 0;
	uint8_t rh_byte1 = 0;
	uint8_t rh_byte2 = 0;
	uint8_t temp_byte1 = 0;
	uint8_t temp_byte2 = 0;
	uint8_t sum = 0;
	uint8_t crc = 0;
	float humidity = 0;
	float temperature = 0;
    uint8_t temp_sign = 0;
    char dht_sensor_type_str[6];

    // Check DHT sensors' readiness
    for (uint8_t i = 0; i < DHT_SENSORS_COUNT; i++)
    {
        if (!DhtSensorCheckReadiness(&(dht_sensors[i])))
        {
            // DHT sensor did not respond. Set its status as NOT ACTIVE
        	DhtSensorSetStatus(&(dht_sensors[i]), DHT_NOT_ACTIVE);
        }
    }

    while (1)
    {
        if (!DhtSensorGetStatus(&(dht_sensors[dht_sensor_idx])))
        {
            // DHT sensor is not active
            if (DhtGetSensorTypeString(&dht_sensors[dht_sensor_idx], dht_sensor_type_str))
            {
    		    sprintf(message1, "*** %s", dht_sensor_type_str);
                sprintf(message2, "*** NOT ACTIVE");
                ShowMessage(message1, message2, 0, 0);
            }
            else
            {
                // Unsupported sensor type
                ShowUnsupportedSensor();
            }

            // Do switch a sensor index
            dht_sensor_idx = SwitchSensorIndex(dht_sensor_idx);

            TIM2MillisecondsDelay(SENSORS_POLLING_PERIOD);
            continue;
        }
    	// Send a request to the DHT sensor
        DhtSendRequest(&(dht_sensors[dht_sensor_idx]));

        // Get a response from the DHT sensor
        if (DhtGetResponse(&(dht_sensors[dht_sensor_idx])))
	    {
        	// Get sensor's response bytes
            rh_byte1 = 0;
            rh_byte2 = 0;
            temp_byte1 = 0;
            temp_byte2 = 0;
            sum = 0;
            crc = 0;

        	// Get DHT sensor's response bytes
        	DhtGetResponsedBytes(&(dht_sensors[dht_sensor_idx]), &rh_byte1, &rh_byte2, &temp_byte1, &temp_byte2, &sum);
        	crc = rh_byte1 + rh_byte2 + temp_byte1 + temp_byte2;

            humidity = 0;
            temperature = 0;
            temp_sign = 0;

        	if (crc == sum)
        	{
                if (dht_sensors[dht_sensor_idx].dht_type == DHT11)
                {

                    if (DhtSerializeData(&dht_sensors[dht_sensor_idx], rh_byte1, rh_byte2,
		                                 temp_byte1, temp_byte2, &temp_sign, &humidity, &temperature))
                    {
                    	ShowDHTData("DHT11", temp_sign, temperature, humidity);
                    }

                }
                else if (dht_sensors[dht_sensor_idx].dht_type == DHT22)
                {

                    if (DhtSerializeData(&dht_sensors[dht_sensor_idx], rh_byte1, rh_byte2,
		                                 temp_byte1, temp_byte2, &temp_sign, &humidity, &temperature))
                    {
                        ShowDHTData("DHT22", temp_sign, temperature, humidity);
                    }

                }
                else
                {
                    // Unsupported sensor type
                    ShowUnsupportedSensor();
                }
        	}
        	else
        	{
                if (DhtGetSensorTypeString(&dht_sensors[dht_sensor_idx], dht_sensor_type_str))
                {
        		    sprintf(message1, "*** %s", dht_sensor_type_str);
	                sprintf(message2, "*** %u != %u", crc, sum);
	                ShowMessage(message1, message2, 0, 0);
                }
                else
                {
                    // Unsupported sensor type
                    ShowUnsupportedSensor();
                }
        	}
      }
	  else
	  {
          // DHT sensor did not respond
		  if (DhtGetSensorTypeString(&dht_sensors[dht_sensor_idx], dht_sensor_type_str))
		  {
			  sprintf(message1, "%s %s %s", "***", dht_sensor_type_str, "***");
              strcpy(message2, "Did not respond");
              ShowMessage(message1, message2, 2, 0);
		  }
          else
          {
              // Unsupported sensor type
              ShowUnsupportedSensor();
          }
	  }

      // Do switch a sensor index
      dht_sensor_idx = SwitchSensorIndex(dht_sensor_idx);

      TIM2MillisecondsDelay(SENSORS_POLLING_PERIOD);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 15;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
