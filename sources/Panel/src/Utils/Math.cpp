#include "defines.h"
#include "Math.h"
#include "FPGA/FPGATypes.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template void Limitation<float>(float *, float, float);
template void Swap<int>(int *, int *);
template int Sign<int>(int);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LowSignedBit(uint value)
{
    int verValue = 1;

    for (int i = 0; i < 32; i++)
    {
        if (verValue & ((int)value))
        {
            return i;
        }

        verValue <<= 1;
    }

    return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool IntInRange(int value, int min, int max)
{
    return (value >= min) && (value <= max);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float MaxFloat(float val1, float val2, float val3)
{
    float retValue = val1;
    if (val2 > retValue)
    {
        retValue = val2;
    }
    if (val3 > retValue)
    {
        retValue = val3;
    }
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Pow10(int pow)
{
    int retValue = 1;

    while (pow--)
    {
        retValue *= 10;
    }

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float RandFloat(float min, float max)
{
    float delta = max - min;
    return min + ((rand() / (float)RAND_MAX) * delta);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool IsEquals(float x, float y)
{
    return fabsf(x - y) < std::numeric_limits<float>::epsilon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FloatsIsEquals(float value0, float value1, float epsilonPart)
{
    float max = fabsf(value0) > fabsf(value1) ? fabsf(value0) : fabsf(value1);

    float epsilonAbs = max * epsilonPart;

    return fabsf(value0 - value1) < epsilonAbs;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>
void Limitation(T *value, T min, T max)
{
    if (*value < min)
    {
        *value = min;
    }
    else if (*value > max)
    {
        *value = max;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
template<class T> 
void Swap(T *value0, T *value1)
{
    T temp = *value0; *value0 = *value1; *value1 = temp;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>
int Sign(T x)
{
    if (x > (T)(0))
    {
        return 1;
    } if (x < (T)(0))
    {
        return -1;
    } return 0;
}

