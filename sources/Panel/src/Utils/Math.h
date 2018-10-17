#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LIMITATION(var, min, max)           if(var < (min)) { (var) = (min); } else if(var > (max)) { var = (max); };

class Math
{
public:
    /// ���������� ������������ �������� �� ���
    static float MaxFloat(float val1, float val2, float val3);
    
    static bool IsEquals(float x, float y);
    /// ���������� ������� ���������� ������ �� ������� value0 � value1
    template<class T> static void Swap(T *value0, T *value1);
    
    template<class T> static int Sign(T x);
    
    template<class T> static void Limitation(T *value, T min, T max);
};
