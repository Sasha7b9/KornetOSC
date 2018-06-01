#pragma once

#ifdef MSVC
#define __attribute(x)
#endif

#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Winvalid-source-encoding"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"


#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>


typedef unsigned char       uchar;
typedef signed char         int8;
typedef unsigned char       uint8;
typedef signed short int    int16;
typedef unsigned short int  uint16;
typedef unsigned int        uint;
typedef uint64_t            uint64;
typedef unsigned int        col_val;


typedef void(*pFuncVV)();
typedef void(*pFuncVB)(bool);

inline void EmptyFuncVV(){}
inline void EmptyFuncVB(bool){};
    

#ifndef _WIN32
#if __ARMCLIB_VERSION < 6070001
#pragma anon_unions
#endif
#endif

typedef union
{
    uint64 dword;
    uint   word[2];
    uint16 halfWord[4];
    uint8  byte[8];
    struct
    {
        uint word0;
        uint word1;
    };
    struct  
    {
        uint16 halfWord0;
        uint16 halfWord1;
        uint16 halfWord2;
        uint16 halfWord3;
    };
    struct
    {
        uint8 byte0;
        uint8 byte1;
        uint8 byte2;
        uint8 byte3;
        uint8 byte4;
        uint8 byte5;
        uint8 byte6;
        uint8 byte7;
    };
} BitSet64;


#define _SET_BIT_VALUE(value, numBit, bitValue) (value |= (bitValue << numBit))
#define _GET_BIT(value, numBit) ((value >> numBit) & 1)
#define _CLEAR_BIT(value, bit) ((value) &= (~(1 << bit)))
#define _SET_BIT(value, bit) ((value) |= (1 << (bit)))


#define _bitset(bits)                               \
  ((uint8)(                                         \
  (((uint8)((uint)bits / 01)        % 010) << 0) |  \
  (((uint8)((uint)bits / 010)       % 010) << 1) |  \
  (((uint8)((uint)bits / 0100)      % 010) << 2) |  \
  (((uint8)((uint)bits / 01000)     % 010) << 3) |  \
  (((uint8)((uint)bits / 010000)    % 010) << 4) |  \
  (((uint8)((uint)bits / 0100000)   % 010) << 5) |  \
  (((uint8)((uint)bits / 01000000)  % 010) << 6) |  \
  (((uint8)((uint)bits / 010000000) % 010) << 7)))


#define BIN_U8(bits) (_bitset(0##bits))

#define BIN_U32(bits3, bits2, bits1, bits0) (BIN_U8(bits3) << 24 | BIN_U8(bits2) << 16 | BIN_U8(bits1) << 8 | BIN_U8(bits0))

#define HEX_FROM_2(hex1, hex0) ((uint)(0x##hex1) << 16 | (uint)0x##hex0)

#define ERROR_VALUE_FLOAT   1.111e29f
#define ERROR_STRING_VALUE  "--.--"
#define ERROR_VALUE_UINT8   255

#define MAX_UINT 0xffffffff


// ��� ����������� ������� ������� ����� ������������ ����� ���������, ����� ����� ����� ���� ���������, ��� ����� ������ ����������
#define CHAR_BUF(name, size)            char name[size]
#define CHAR_BUF2(name, size1, size2)   char name[size1][size2]


#define ENABLE_RU "���"
#define ENABLE_EN "On"

#define DISABLE_RU "����"
#define DISABLE_EN "Off"
