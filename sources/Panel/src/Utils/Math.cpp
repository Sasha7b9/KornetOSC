#include "defines.h"
#include "Math.h"
#include "FPGA/FPGATypes.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template void Math::Limitation<float>(float *, float, float);
template void Math::Swap<int>(int *, int *);
template int Math::Sign<int>(int);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Math::MaxFloat(float val1, float val2, float val3)
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
bool Math::IsEquals(float x, float y)
{
    return fabsf(x - y) < std::numeric_limits<float>::epsilon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>
void Math::Limitation(T *value, T min, T max)
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
void Math::Swap(T *value0, T *value1)
{
    T temp = *value0; *value0 = *value1; *value1 = temp;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
template<class T>
int Math::Sign(T x)
{
    if (x > (T)(0))
    {
        return 1;
    } if (x < (T)(0))
    {
        return -1;
    } return 0;
}

