#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LIMITATION(var, min, max)           if(var < (min)) { (var) = (min); } else if(var > (max)) { var = (max); };

/// Возвращает максимальное значение из трёх
float MaxFloat(float val1, float val2, float val3);

bool IsEquals(float x, float y);

/// Вычисление 10**pow.
int Pow10(int pow);

/// Обменивает местами содержимое памяти по адресам value0 и value1
template<class T> void Swap(T *value0, T *value1);

template<class T> int Sign(T x);

template<class T> void Limitation(T *value, T min, T max);
