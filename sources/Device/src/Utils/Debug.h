#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Debug
{
public:
    static void StartProfiling();
    static void PointProfiling(char *name);

    static void ClearTimeCounter();
    static void StartIncreaseCounter();
    static void StopIncreaseCounter();
    static uint GetTimeCounterUS();
private:
    static uint timeStart;
    static uint timeCounter;
    static uint timeStartCounter;
};
