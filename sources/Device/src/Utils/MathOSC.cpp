#include "defines.h"
#include "MathOSC.h"
#include "FPGA/FPGA.h"
#include "FPGA/RShift.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
volatile const float absStepRShift[] =
{
    2e-3f   / 20 / STEP_RSHIFT,
    5e-3f   / 20 / STEP_RSHIFT,
    10e-3f  / 20 / STEP_RSHIFT,
    20e-3f  / 20 / STEP_RSHIFT,
    50e-3f  / 20 / STEP_RSHIFT,
    100e-3f / 20 / STEP_RSHIFT,
    200e-3f / 20 / STEP_RSHIFT,
    500e-3f / 20 / STEP_RSHIFT,
    1.0f    / 20 / STEP_RSHIFT,
    2.0f    / 20 / STEP_RSHIFT,
    5.0f    / 20 / STEP_RSHIFT,
    10.0f   / 20 / STEP_RSHIFT,
    20.0f   / 20 / STEP_RSHIFT
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MathOSC::NumDigitsInIntPart(float value)
{
    float fabsValue = fabsf(value);

    int numDigitsInInt = 0;
    if (fabsValue >= 10000)
    {
        numDigitsInInt = 5;
    }
    else if (fabsValue >= 1000)
    {
        numDigitsInInt = 4;
    }
    else if (fabsValue >= 100)
    {
        numDigitsInInt = 3;
    }
    else if (fabsValue >= 10)
    {
        numDigitsInInt = 2;
    }
    else
    {
        numDigitsInInt = 1;
    }

    return numDigitsInInt;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *MathOSC::Bin2String(uint8 value, char buffer[9])
{
    for (int bit = 0; bit < 8; bit++)
    {
        buffer[7 - bit] = _GET_BIT(value, bit) ? '1' : '0';
    }
    buffer[8] = '\0';
    return buffer;
}
