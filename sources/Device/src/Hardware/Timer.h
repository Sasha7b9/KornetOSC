#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum TypeTimer
{
    kPressKey,                  ///< ����� �������������, ����� �������� ������� �������.
    kShowLevelRShiftA,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 1.
    kShowLevelRShiftB,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 2.
    kShowLevelTrigLev,          ///< ����� �������������, ����� ���������� ��������� ����� ������ �������������
    kENumSignalsInSec,          ///< ��� ��������� ���������� ���������� ������� � �������.
    kFlashDisplay,              ///< ������ ��� ��������� �������� ������ �����-������ �������.
    kShowMessages,              ///< ������ ��� ��������� ����� ������ �������������� � ��������������� ���������.
    kMenuAutoHide,              ///< ������ ��� ������� ������� ��������� ����.
    kRShiftMarkersAutoHide,     ///< ������ ��� ������� ������� ��������� �������������� ������� �����.
    kUSB,                       ///< ���������������, ��� ����� ����.
    kStopSound,                 ///< ��������� ����
    kTemporaryPauseFPGA,        ///< ��������� ����� ��� �������� ������� �� ������ ����� �������� �����
    kStrNaviAutoHide,           ///< ������� ������ ��������� ����
    kTimerStartP2P,             ///< ������ ��� ������� ���������� ����� ����������� ������
    kTimerDisplay,              ///< ������ �� ������ ��������� ������
    kTemp,
    NumTimers
};

class Timer
{
public:

    static void Init();

    static void Disable(TypeTimer type);

    static void SetAndStartOnce(TypeTimer type, pFuncVV func, uint dTms);

    static void PauseOnTime(uint timeMS);

    static void SetAndEnable(TypeTimer type, pFuncVV func, uint dTms);
    /// ��������� ������� timer ������� � ����� ������������
    static void Set(TypeTimer type, pFuncVV func, uint dTms);

    static void Enable(TypeTimer type);

    static bool IsRun(TypeTimer type);

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
