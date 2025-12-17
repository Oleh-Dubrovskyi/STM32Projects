/**
  ************************************************************************************
  * @file      : dht.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Implementation of API functions to communicate with DHT11 and DHT22 sensors
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

#include "../Inc/dht.h"
#include "../../DelayMicro/Inc/delay_micro.h"

// Maximum attempts count of the DHT sensor's readiness check
static const uint8_t MAX_DHT_CHECK_ATTEMPTS_COUNT = 3;
// DHT sensor's readiness check period
static const uint32_t DHT_SENSOR_CHECK_PERIOD = 500;

// Start signal duration for DHT11
// When the communication between MCU and DHT11 begins,
// the program of MCU will set Data Single-bus voltage level from high to low
// and this process must take at least 18ms
static const uint8_t DHT11_START_SIGNAL_DURATION = 18;

// Start signal duration for DHT22
// When the communication between MCU and DHT22 begins,
// the program of MCU will transform data-bus's voltage level from high to low level
// and this process must beyond at least 1ms
static const uint8_t DHT22_START_SIGNAL_DURATION = 2;

// DHT sensor response wait time (for DHT11 and DHT22)
// The MCU will pull up voltage and wait 20-40us for DHT’s response.
static const uint8_t DHT_RESPONSE_WAIT_TIME = 40;

// DHT sensor low level response signal duration (for DHT11 and DHT22)
// When DATA Single-Bus is at the low voltage level, this means that DHT is sending the response signal.
static const uint8_t DHT_LL_RESPONSE_SIGNAL_DURATION = 80;

// DHT sensor high level signal duration (for DHT11 and DHT22)
// Once DHT sent out the response signal, it pulls up voltage and keeps it for 80us and prepares for data transmission.
static const uint8_t DHT_HL_SIGNAL_DURATION = 80;

// Low-level prefix duration for DHT sensor data bit (for DHT11 and DHT22)
// When DHT is sending data to MCU, every bit of data begins with the 50us low-voltage-level
static const uint8_t DHT_LL_DATA_BIT_PREFIX_DURATION = 50;

// High-level signal duration for zero data bit of the DHT sensor (for DHT11 and DHT22)
// The length of the high-voltage-level signal determines whether data bit is "0" or "1"
// 26-28us voltage-length means data "0"
// 70us voltage-length means data "1"
static const uint8_t DHT_HL_ZERO_DATA_BIT_DURATION = 28;

// Configure DHT sensor
void DhtConfigureSensor(DHTSensor * p_dht_sensor, DHTType dht_type, DHTGpioDataLine data_line)
{
    p_dht_sensor->dht_type = dht_type;
    p_dht_sensor->dht_gpio_data_line.gpio_type = data_line.gpio_type;
    p_dht_sensor->dht_gpio_data_line.gpio_pin = data_line.gpio_pin;
    switch(dht_type)
    {
    case DHT11:
        p_dht_sensor->dht_start_signal_duration = DHT11_START_SIGNAL_DURATION;
    	break;
    case DHT22:
        p_dht_sensor->dht_start_signal_duration = DHT22_START_SIGNAL_DURATION;
    	break;
    default:
    	p_dht_sensor->dht_type = DHT_Unknown;
    	p_dht_sensor->dht_status = DHT_NOT_ACTIVE;
    	return;
    }

    p_dht_sensor->dht_status = DHT_ACTIVE;
}

// Get DHT sensor's status
DHTStatus DhtSensorGetStatus(DHTSensor * p_dht_sensor)
{
	return p_dht_sensor->dht_status;
}

// Set DHT sensor's status
void DhtSensorSetStatus(DHTSensor * p_dht_sensor, DHTStatus dht_status)
{
	p_dht_sensor->dht_status = dht_status;
}

// Send a request to the DHT sensor
void DhtSendRequest(DHTSensor * p_dht_sensor)
{
    if (p_dht_sensor->dht_type == DHT_Unknown)
    {
        return;
    }
	// Configure DHT sensor's Data Line as Output to write
	DhtConfigureDataLinePin(p_dht_sensor, OUTPUT_MODE);
    // Set the DHT sensor's Data Single-bus voltage level to low
    HAL_GPIO_WritePin(p_dht_sensor->dht_gpio_data_line.gpio_type,
    		          p_dht_sensor->dht_gpio_data_line.gpio_pin, GPIO_PIN_RESET);

    TIM2MillisecondsDelay(p_dht_sensor->dht_start_signal_duration);

    // Pull up the DHT sensor's  Data Single-bus voltage
    HAL_GPIO_WritePin(p_dht_sensor->dht_gpio_data_line.gpio_type, p_dht_sensor->dht_gpio_data_line.gpio_pin, GPIO_PIN_SET);
    // Configure DHT sensor's Data Line as Input to wait for response
    DhtConfigureDataLinePin(p_dht_sensor, INPUT_MODE);
}

// Enable GPIOx clock for the DHT sensor's data line port
void DhtEnableGPIOXClock(DHTSensor * p_dht_sensor)
{
	if (p_dht_sensor->dht_gpio_data_line.gpio_type == GPIOA)
	{
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if (p_dht_sensor->dht_gpio_data_line.gpio_type == GPIOB)
	{
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if (p_dht_sensor->dht_gpio_data_line.gpio_type == GPIOC)
	{
	    __HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if (p_dht_sensor->dht_gpio_data_line.gpio_type == GPIOH)
	{
	    __HAL_RCC_GPIOH_CLK_ENABLE();
	}
}

// Configure DHT sensor's data line pin as Input or Output
void DhtConfigureDataLinePin(DHTSensor * p_dht_sensor, DHTDataLineMode in_out)
{
	DhtEnableGPIOXClock(p_dht_sensor);

    // Configure data line pin
	GPIO_InitTypeDef gpio_init_struct = {0};
	gpio_init_struct.Pull = GPIO_NOPULL;
	gpio_init_struct.Pin = p_dht_sensor->dht_gpio_data_line.gpio_pin;

	if (in_out == OUTPUT_MODE)
    {
    	// Configure data line pin as Output
		gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    }
    else
    {
    	// Configure data line pin as Input
    	gpio_init_struct.Mode = GPIO_MODE_INPUT;
    }

	HAL_GPIO_Init(p_dht_sensor->dht_gpio_data_line.gpio_type, &gpio_init_struct);
}

// Get a response from the DHT sensor
uint8_t DhtGetResponse(DHTSensor * p_dht_sensor)
{
    uint8_t wait_time = DHT_RESPONSE_WAIT_TIME;
    uint8_t is_response_ok = 0;

    // Wait 20-40us for DHT's response: the DHT sensor should set Data Single-bus voltage level from high to low
    while((HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
                            p_dht_sensor->dht_gpio_data_line.gpio_pin)) && wait_time > 0)
    {
    	TIM2MicrosecondsDelay(1);
    	wait_time--;
    }

    if (!(HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type, p_dht_sensor->dht_gpio_data_line.gpio_pin)))
    {
    	// The DHT sensor sent out a low-voltage-level response signal: the DHT sensor's Data Single-bus voltage level is low
    	wait_time = DHT_LL_RESPONSE_SIGNAL_DURATION;
    	// The low-voltage-level response signal should last 80us
    	// Wait until 80us, while the sensor sets the Signal-bus voltage to a high level
        while(!(HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
                                 p_dht_sensor->dht_gpio_data_line.gpio_pin)) && wait_time > 0)
        {
        	TIM2MicrosecondsDelay(1);
        	wait_time--;
        }

    	if ((HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type, p_dht_sensor->dht_gpio_data_line.gpio_pin)))
    	{
            // The DHT sensor has set Data Single-bus voltage level from low to high
    		// The high level should be kept by DHT sensor during 80us
    		wait_time = DHT_HL_SIGNAL_DURATION;
    		// Wait until 80us, while the sensor sets the Signal-bus voltage to a low level and starts data transmission
    		while((HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
    		                        p_dht_sensor->dht_gpio_data_line.gpio_pin)) && wait_time > 0)
    		{
    			TIM2MicrosecondsDelay(1);
    			wait_time--;
    		}

    		is_response_ok = 1;
    	}

    }

    return is_response_ok;
}

// Get DHT sensor's response bytes
uint8_t DhtGetResponsedBytes(DHTSensor * p_dht_sensor,
                             uint8_t * rh_byte1, uint8_t * rh_byte2,
                             uint8_t * temp_byte1, uint8_t * temp_byte2, uint8_t * sum)
{
	uint8_t dht_crc = 0;

	*rh_byte1 = 0;
	*rh_byte2 = 0;
	*temp_byte1 = 0;
	*temp_byte2 = 0;
	*sum = 0;

	// Get Humidity
	*rh_byte1 = DhtReadByte(p_dht_sensor);
    *rh_byte2 = DhtReadByte(p_dht_sensor);
    // Get Temperature
    *temp_byte1 = DhtReadByte(p_dht_sensor);
    *temp_byte2 = DhtReadByte(p_dht_sensor);

    // Get CRC from the DHT sensor
    *sum = DhtReadByte(p_dht_sensor);

    // Calculate CRC
    dht_crc = *rh_byte1 + *rh_byte2 + *temp_byte1 + *temp_byte2;

    // Check CRC
    if (*sum == dht_crc)
    {
        return 1;
    }
    else
    {
    	return 0;
    }
}

// Read DHT sensor's response byte
uint8_t DhtReadByte(DHTSensor * p_dht_sensor)
{
    uint8_t result = 0;
    uint8_t j;

    // Do read 8 bits for the current byte
    for (j=0; j < 8; j++)
    {
        // Every bit of data begins with the 50us low-voltage-level
        uint8_t wait_time = DHT_LL_DATA_BIT_PREFIX_DURATION;
    	while (!(HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
    	                          p_dht_sensor->dht_gpio_data_line.gpio_pin)) && wait_time > 0)
        {
            // Wait for the pin to go high
    		TIM2MicrosecondsDelay(1);
    		wait_time--;
        }

        // Check the DHT11 data line pin is still low
        while (!(HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
                                  p_dht_sensor->dht_gpio_data_line.gpio_pin)));
        // Wait for 28us
    	TIM2MicrosecondsDelay(DHT_HL_ZERO_DATA_BIT_DURATION);
        if (!(HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
                               p_dht_sensor->dht_gpio_data_line.gpio_pin)))
        {
        	//  26-28us high voltage-length means data bit "0"
            // Do nothing
        }
        else
        {
        	// Pin is high; bit is 1
        	result |= (1<<(7-j));
        	// Wait for the pin to go low
        	while ((HAL_GPIO_ReadPin(p_dht_sensor->dht_gpio_data_line.gpio_type,
                                     p_dht_sensor->dht_gpio_data_line.gpio_pin)));
        }
    }

    return result;
}

// Serialize DHT sensor's response
uint8_t DhtSerializeData(DHTSensor * p_dht_sensor,
		                 uint8_t rh_byte1, uint8_t rh_byte2,
		                 uint8_t temp_byte1, uint8_t temp_byte2,
						 uint8_t * temp_sign, float * humidity, float * temperature)
{
	if (p_dht_sensor->dht_type == DHT11)
	{
        *humidity = (float)(rh_byte1);  // rh_byte2 should be equal to 0
    	*temperature = (float)(temp_byte1);  // temp_byte2 should be equal to 0
    	*temp_sign = 0;
	}
	else if (p_dht_sensor->dht_type == DHT22)
	{
	    *humidity = (float)((((uint16_t)rh_byte1) << 8) | (uint16_t)rh_byte2)/10.0;
	    *temperature = (float)((((uint16_t)(temp_byte1 & 0x7f) << 8)) | (uint16_t)temp_byte2)/10.0;
        *temp_sign = temp_byte1 >> 7;
	}
	else
	{
        return 0;
	}

    return 1;
}

// Get DHT sensor type string
uint8_t DhtGetSensorTypeString(DHTSensor * p_dht_sensor, char * dht_sensor_type_string)
{
    if (p_dht_sensor->dht_type == DHT11)
    {
    	strcpy(dht_sensor_type_string, "DHT11");
    }
    else if (p_dht_sensor->dht_type == DHT22)
    {
    	strcpy(dht_sensor_type_string, "DHT22");
    }
    else
    {
        return 0;
    }

    return 1;
}

// Check DHT sensor's readiness
uint8_t DhtSensorCheckReadiness(DHTSensor * p_dht_sensor)
{

    for (uint8_t i = 0; i < MAX_DHT_CHECK_ATTEMPTS_COUNT; i++)
    {
    	// Send a request to the DHT sensor
        DhtSendRequest(p_dht_sensor);
        // Get a response from the DHT sensor
        if (DhtGetResponse(p_dht_sensor))
	    {
        	return 1;
	    }
        TIM2MillisecondsDelay(DHT_SENSOR_CHECK_PERIOD);
    }

    return 0;
}
