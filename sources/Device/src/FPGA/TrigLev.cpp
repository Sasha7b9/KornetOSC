#include "TrigLev.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Trig::pulse = false;
uint Trig::timeSwitchingTrig = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Trig::SyncPulse()
{
    return pulse;
}
