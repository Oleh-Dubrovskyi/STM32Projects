/*
 * lcd1602_custom.h
 *
 *  Created on: Aug 20, 2025
 *      Author: Oleh
 */

#ifndef INC_LCD1602_CUSTOM_H_
#define INC_LCD1602_CUSTOM_H_

// Custom symbols
// Cyrilic symbols
#define BIG_BE 1
#define LITTLE_BE 2
#define BIG_GE 3
#define LITTLE_GE 4

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

#endif /* INC_LCD1602_CUSTOM_H_ */
