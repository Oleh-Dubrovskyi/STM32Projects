/**
  ************************************************************************************
  * @file      : dht.h
  * @author    : Oleh Dubrovskyi
  * @brief     : Header for dht.c file.
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

#ifndef INC_DHT_H
#define INC_DHT_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

// DHT sensor types enumerator
typedef enum
{
	DHT_Unknown = 0,
    DHT11,
    DHT22
} DHTType;

// DHT sensor data line modes enumerator
typedef enum
{
    INPUT_MODE = 0,
	OUTPUT_MODE
} DHTDataLineMode;

// DHT sensor status enumerator
typedef enum
{
    DHT_NOT_ACTIVE = 0,
	DHT_ACTIVE
} DHTStatus;

// DHT sensor GPIO pin data line description structure
typedef struct
{
	GPIO_TypeDef * gpio_type;
	uint16_t gpio_pin;
} DHTGpioDataLine;

// DHT sensor description structure
typedef struct
{
	DHTType dht_type;
	DHTGpioDataLine dht_gpio_data_line;
	DHTStatus dht_status;
	uint8_t dht_start_signal_duration;
} DHTSensor;

// Configure DHT sensor
void DhtConfigureSensor(DHTSensor * p_dht_sensor, DHTType dht_type, DHTGpioDataLine data_line);

// Get DHT sensor's status
DHTStatus DhtSensorGetStatus(DHTSensor * p_dht_sensor);

// Set DHT sensor's status
void DhtSensorSetStatus(DHTSensor * p_dht_sensor, DHTStatus dht_status);

// Send a request to the DHT sensor
void DhtSendRequest(DHTSensor * p_dht_sensor);

// Get a response from the DHT sensor
uint8_t DhtGetResponse(DHTSensor * p_dht_sensor);

// Get DHT sensor's response bytes
uint8_t DhtGetResponsedBytes(DHTSensor * p_dht_sensor,
                             uint8_t * rh_byte1, uint8_t * rh_byte2,
                             uint8_t * temp_byte1, uint8_t * temp_byte2, uint8_t * sum);

// Configure DHT sensor's data line pin as Input or Output
void DhtConfigureDataLinePin(DHTSensor * p_dht_sensor, DHTDataLineMode in_out);

// Enable GPIOx clock for the DHT sensor's data line port
void DhtEnableGPIOXClock();

// Read DHT sensor's response byte
uint8_t DhtReadByte(DHTSensor * p_dht_sensor);

// Serialize DHT sensor's response
uint8_t DhtSerializeData(DHTSensor * p_dht_sensor,
		                 uint8_t rh_byte1, uint8_t rh_byte2,
		                 uint8_t temp_byte1, uint8_t temp_byte2,
						 uint8_t * temp_sign, float * humidity, float * temperature);

// Get DHT sensor type string
uint8_t DhtGetSensorTypeString(DHTSensor * p_dht_sensor, char * dht_sensor_type_string);

// Check DHT sensor's readiness
uint8_t DhtSensorCheckReadiness(DHTSensor * p_dht_sensor);

#endif // INC_DHT_H
