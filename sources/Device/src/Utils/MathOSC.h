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
