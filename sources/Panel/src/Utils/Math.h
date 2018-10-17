#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LIMITATION(var, min, max)           if(var < (min)) { (var) = (min); } else if(var > (max)) { var = (max); };

/// Возвращает true, если value входит в диапазон [min; max]
bool IntInRange(int value, int min, int max);
/// Возвращает номер младшего бита, равного единице
int LowSignedBit(uint value);
/// Возвращает максимальное значение из трёх
float MaxFloat(float val1, float val2, float val3);
/// \brief Сравнивает два числа. Возвращает true, если числа отличаются друг от друга не более, чем на epsilonPart. При этом для расчёта epsilonPart 
/// используется большее в смысле модуля число.
bool FloatsIsEquals(float value0, float value1, float epsilonPart);

bool IsEquals(float x, float y);

float RandFloat(float min, float max);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Math
{
public:
    static void Smoothing(uint8 *data, int numPoints, int numSmooth);
    
    static int MinFrom2Int(int val0, int val1);

    static uint8 MaxFromArray_RAM(const uint16 *data, int firstPoint, int lastPoint);

    static uint8 MinFromArray_RAM(const uint16 *data, int firstPoint, int lastPoint);

    static uint8 MaxFromArray(const uint8 *data, int firstPoint, int lastPoint);

    static uint8 MinFromArray(const uint8 *data, int firstPoint, int lastPoint);

    static uint8 MaxFromArrayWithErrorCode(const uint8 *data, int firstPoint, int lastPoint);

    static uint8 MinFromArrayWithErrorCode(const uint8 *data, int firstPoint, int lastPoint);
    /// \brief Возвращает координату x пересечения линии, проходящей через (x0, y0), (x1, y1), с горизонтальной линией, проходящей через точку с 
    /// ординатой yHorLine.
    static float GetIntersectionWithHorizontalLine(int x0, int y0, int x1, int y1, int yHorLine);

    static uint8 CalculateFiltr(const uint8 *data, int x, int numPoints, int numSmoothing);

    static void CalculateFiltrArray(const uint8 *dataIn, uint8 *dataOut, int numPoints, int numSmoothing);
    /// Найти первый элемент массива, не соотвествующий заданному
    static int FindAnotherElement(uint8 *data, uint8 value, int numElements);

    static int DigitsInIntPart(float value);
    /// \brief Округляет число с плавающей точкой. numDigits - полное число знаков, по которым производится округление.
    /// Например, RoundFloat(12.37137, 4) округлит до 12.40)
    static float RoundFloat(float value, int numDigits);
};


/// Вычисление 10**pow.
int Pow10(int pow);

/// Обменивает местами содержимое памяти по адресам value0 и value1
template<class T> void Swap(T *value0, T *value1);

template<class T> int Sign(T x);

template<class T> void Limitation(T *value, T min, T max);

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
