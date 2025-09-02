/**
  ************************************************************************************
  * @file      : dth11.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to communicate with DHT11 sensor
  *            : associated with STM32F401RExx devices
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

#include <stdio.h>
#include <string.h>

#include "../../DelayMicro/Inc/delay_micro.h"
#include "../Inc/dht11.h"

const float DHT11_SCALE = 256.0;

DTH11GpioDataLine g_dth11_gpio_data_line = {GPIOA, GPIO_PIN_0};

// Configure DHT11 data line
void Dht11ConfigureDataLine(DTH11GpioDataLine data_line)
{
	g_dth11_gpio_data_line.gpio_type = data_line.gpio_type;
	g_dth11_gpio_data_line.gpio_pin = data_line.gpio_pin;
}

// Send a request to the DHT11 sensor
void Dht11SendRequest()
{
    // Set DHT11 Data Line Pin as Output to write
	Dht11SetDataLinePinOutput();
	// Set the DHT11 Data Single-bus voltage level to low
	HAL_GPIO_WritePin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin, GPIO_PIN_RESET);
	TIM2MillisecondsDelay(18);
	// Pull up the DHT11 Data Single-bus voltage
	HAL_GPIO_WritePin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin, GPIO_PIN_SET);
	// Set DHT11 Data Line Pin as Input to wait for response
	Dht11SetDataLinePinInput();
}

// Enable GPIOx clock for the Dht11 data line port
void Dht11EnableGPIOXClock()
{
	if (g_dth11_gpio_data_line.gpio_type == GPIOA)
	{
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if (g_dth11_gpio_data_line.gpio_type == GPIOB)
	{
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if (g_dth11_gpio_data_line.gpio_type == GPIOC)
	{
	    __HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if (g_dth11_gpio_data_line.gpio_type == GPIOH)
	{
	    __HAL_RCC_GPIOH_CLK_ENABLE();
	}
}

// Set DHT11 data line pin Input
void Dht11SetDataLinePinInput()
{
    // Enable GPIOx clock
	Dht11EnableGPIOXClock();

	// Configure data line pin as Input
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = g_dth11_gpio_data_line.gpio_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// Set DHT11 data line pin Output
void Dht11SetDataLinePinOutput()
{
    // Enable GPIOx clock
	Dht11EnableGPIOXClock();

	// Configure data line pin as Output
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = g_dth11_gpio_data_line.gpio_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// Get a response from the DHT11 sensor
uint8_t Dht11GetResponse()
{
    uint8_t timeout = 40;
    uint8_t is_response_ok = 0;

    // Wait 20-40us for DHT's response: the DHT11 should set Data Single-bus voltage level from high to low
    while((HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)) && timeout > 0)
    {
    	TIM2MicrosecondsDelay(1);
    	timeout--;
    }

    if (!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)))
    {
    	// The DHT11 sent out a low-voltage-level response signal: the DHT11 Data Single-bus voltage level is low
    	timeout = 80;
    	// The low-voltage-level response signal should last 80us
    	// Wait until 80us, while the sensor sets the Signal-bus voltage to a high level
        while(!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)) && timeout > 0)
        {
        	TIM2MicrosecondsDelay(1);
        	timeout--;
        }

    	if ((HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)))
    	{
            // The DHT11 sets Data Single-bus voltage level from low to high
    		// The high level should be kept by DHT11 during 80us
    		timeout = 80;
    		// Wait until 80us, while the sensor sets the Signal-bus voltage to a low level and starts data transmission
    		while((HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)) && timeout > 0)
    		{
    			TIM2MicrosecondsDelay(1);
            	timeout--;
    		}
    		is_response_ok = 1;

    		return is_response_ok;
    	}

    }

    return is_response_ok;
}

// Get responsed bytes
uint8_t Dht11GetResponsedBytes(uint8_t * rh_byte1, uint8_t * rh_byte2,
		                       uint8_t * temp_byte1, uint8_t * temp_byte2, uint8_t * sum)
{
	uint8_t dht11_crc = 0;

	*rh_byte1 = 0;
	*rh_byte2 = 0;
	*temp_byte1 = 0;
	*temp_byte2 = 0;
	*sum = 0;

	// Get Humidity
	*rh_byte1 = Dht11ReadByte();
    *rh_byte2 = Dht11ReadByte();
    // Get Temperature
    *temp_byte1 = Dht11ReadByte();
    *temp_byte2 = Dht11ReadByte();

    // Get CRC from the DHT11 sensor
    *sum = Dht11ReadByte();

    // Calculate CRC
    dht11_crc = *rh_byte1 + *rh_byte2 + *temp_byte1 + *temp_byte2;

    // Check CRC
    if (*sum == dht11_crc)
    {
        return 1;
    }
    else
    {
    	return 0;
    }
}

// Read byte from response
uint8_t Dht11ReadByte()
{
    uint8_t result = 0;
    uint8_t j;

    // Do read 8 bits for the current byte
    for (j=0; j < 8; j++)
    {
        // Every bit of data begins with the 50us low-voltage-level
        uint8_t timeout = 50;
    	while (!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)) && timeout > 0)
        {
            // Wait for the pin to go high
    		TIM2MicrosecondsDelay(1);
            timeout--;
        }

        // Check the DHT11 data line pin is still low
        while (!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)));
        // Wait for 28us
    	TIM2MicrosecondsDelay(28);
        if (!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)))
        {
        	//  26-28us high voltage-length means data bit "0"
            // Do nothing
        }
        else
        {
        	// Pin is high; bit is 1
        	result |= (1<<(7-j));
        	// Wait for the pin to go low
        	while ((HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)));
        }
        // When the last bit data is transmitted, DHT11 pulls down the voltage level and keeps it for 50us.
        //timeout = 50;
        //while (!(HAL_GPIO_ReadPin(g_dth11_gpio_data_line.gpio_type, g_dth11_gpio_data_line.gpio_pin)) && timeout > 0);
    }

    return result;
}


