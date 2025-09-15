/**
  ***************************************************************************************
  * @file      : lcd1602_custom.c
  * @author    : Oleh Dubrovskyi
  * @brief     : Definition of the custom symbols patterns as examples
  ***************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 Oleh Dubrovskyi.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ***************************************************************************************
 */

#include "../../Lcd1602_i2c/Inc/lcd1602_custom.h"

char PATTERN_BIG_BE[] =
{
    0b00011110,
    0b00010000,
    0b00010000,
    0b00011100,
    0b00010010,
    0b00010010,
    0b00011100,
    0b00000000
};

char PATTERN_LITTLE_BE[] =
{
    0b00000000,
    0b00000000,
    0b00011111,
    0b00010000,
    0b00011110,
    0b00010001,
    0b00011110,
    0b00000000
};

char PATTERN_BIG_GE[] =
{
    0b00011111,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00000000
};

char PATTERN_LITTLE_GE[] =
{
    0b00000000,
    0b00000000,
    0b00011111,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00000000
};
