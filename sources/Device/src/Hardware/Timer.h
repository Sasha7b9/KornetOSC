#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:

    static void Init();

private:
};


/// ��������� ������� ��� ��������� ����� �������� ������� (����� � �����������). �������� ������� ���-�� �� 30 ������.
#define START_MULTI_MEASUREMENT()   { TIM2->CR1 &= (uint)~TIM_CR1_CEN; TIM2->CNT = 0; TIM2->CR1 |= TIM_CR1_CEN; }
/// ���������� ��������� ������ � ���������� ������ START_MULTI_MEASUREMENT
#define TIME_TICKS  (TIM2->CNT)
/// ���������� ��������� ����������� � ���������� ������� START_MULTI_MEASUREMENT
#define TIME_US     (TIME_TICKS / 90)
/// ���������� �����������, ��������� � ������ ������ ���������
#define TIME_MS     HAL_GetTick()

#define PAUSE_ON_TICKS(x)   { uint time = TIME_TICKS; while(time + (x) > TIME_TICKS) {}; }
#define PAUSE_ON_US(x)      { uint time = TIME_US; while (TIME_US - time < (x)) {}; }
#define PAUSE_ON_MS(x)      { uint time = TIME_MS; while (TIME_MS - time < (x)) {}; }
