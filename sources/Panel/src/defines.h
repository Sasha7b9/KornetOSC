#pragma once

#ifdef MSVC
#define __attribute(x)
#endif

#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wchar-subscripts"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Winvalid-source-encoding"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wformat-nonliteral"

#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>


typedef unsigned int        uint;
typedef unsigned short int  uint16;
typedef signed short int    int16;
typedef unsigned char       uint8;
typedef unsigned char       uchar;
typedef signed char         int8;

typedef void(*pFuncVV)(void);

#ifdef WIN32
typedef unsigned int uint32_t;
#endif

enum Color
{
    COLOR_BACK = 0x00,
    COLOR_FILL = 0x01
};


#define TIME_UPDATE_KEYBOARD 2   ///< Время между опросами клавиатуры
