#pragma once
#include "FPGA/FPGA.h"
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define RSHIFT_2_ABS(rShift, range) (-(RShift::ZERO - (rShift)) * absStepRShift[(uint)(range)])


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//extern const float absStepRShift[];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MathOSC
{
public:

    template<class T>
    static void CircleIncrease(T &value, int min, int max)
    {
        if (value < max)
        {
            ++value;
        }
        else
        {
            value = (uint8)min;
        }
    }

    template<class T>
    static void LimitationIncrease(T *value, T max)
    {
        if ((*value) < max) { ++(*value); }
    }

    /// Инкрементировать *value, но не больше, чем max
    template<class T>
    static void LimitationDecrease(T *value, T min)
    {
        if (*value > min)  { --(*value); }
    }

    /// Прибавить к *value term и ограничить, если результат выходит за границы [min, max]
    template<class T>
    static void AddtionThisLimitation(T *value, int term, T min, T max)
    {
        if (term > 0)
        {
            if (max - term >= *value)
            {
                *value += term;
            }
            else
            {
                *value = max;
            }
        }
        else
        {
            if (min - term <= *value)
            {
                *value += term;
            }
            else
            {
                *value = min;
            }
        }
    }

    /// Переводит значение voltage в тествоый вид в готовом для вывода на экран виде
    static char *Voltage2String(float voltage, bool alwaysSign, char buffer[20]);
    /// Переводит число с плавающей точкой в текстовый вид. numDigits - число цифровых знакомест
    static char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20]);

    template<class T>
    static void Limitation(T *value, T min, T max)
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

    static int LowSignedBit(uint value);

    char *Bin2String16(uint16 value, char valBuffer[19]);

    template<class T>
    static int Sign(T x)
    {
        if (x > (T)(0)) { return 1; }
        if (x < (T)(0)) { return -1; }
        return 0;
    }

    template<class T>
    static void Smoothing(T *data, int numPoints, int numSmooth)
    {
        if (numSmooth == 0 || numSmooth == 1)
        {
            return;
        }

        float *buffer = (float *)malloc((uint)numPoints);
        int *num = (int *)malloc((uint)numPoints);

        for (int i = 1; i < numPoints; i++)
        {
            buffer[i] = 0.0f;

            num[i] = 0;
            for (int j = -numSmooth / 2; j < numSmooth / 2; j++)
            {
                int index = i + j;
                if (index >= 1 && index < numPoints)
                {
                    buffer[i] += data[index];
                    ++num[i];
                }
            }
        }

        for (int i = 1; i < numPoints; i++)
        {
            data[i] = (T)(buffer[i] / num[i] + 0.5f);
        }

        free(buffer);
        free(num);
    }

private:
    static int NumDigitsInIntPart(float value);

    char *Bin2String(uint8 value, char buffer[9]);
};
