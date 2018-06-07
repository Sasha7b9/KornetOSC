#include "Timer.h"
#include "defines.h"
#include "Hardware/stm32/Timer4XX.h"
#include <limits.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TimerStruct
{
    pFuncVV func;       // Функция таймера
    uint    dTms;          // Период срабатывания, мс
    uint    timeNextMS;    // Время следующего срабатывания. Если == 0xffffffff, то таймер неактивен
    bool    repeat;        // Если true, будет срабатывать, пока не будет вызвана функция Timer_Disable()
    uint8   notUsed0;
    uint8   notUsed1;
    uint8   notUsed2;
};

static TimerStruct timers[NumTimers];

static Timer4XX tim3;   // Для таймеров

#define TIME_NEXT(type) (timers[type].timeNextMS)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Timer::Init()
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM_HandleTypeDef handleTIM2 =
    {
        TIM2,
        {
            0,
            TIM_COUNTERMODE_UP,
            (uint)-1,
            TIM_CLOCKDIVISION_DIV1
        }
    };
    HAL_TIM_Base_Init(&handleTIM2);
    HAL_TIM_Base_Start(&handleTIM2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::SetAndStartOnce(TypeTimer type, pFuncVV func, uint dTms)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::SetAndEnable(TypeTimer type, pFuncVV func, uint dTms)
{
    Set(type, func, dTms);
    Enable(type);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Set(TypeTimer type, pFuncVV func, uint dTms)
{
    TimerStruct *timer = &timers[type];
    timer->func = func;
    timer->dTms = dTms;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static uint NearestTime()
{
    uint time = UINT_MAX;

    for (uint type = 0; type < NumTimers; type++)
    {
        if (TIME_NEXT(type) < time)
        {
            time = TIME_NEXT(type);
        }
    }

    return time;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTIM()
{
    tim3.StopIT();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StartTIM(uint timeStopMS)
{
    StopTIM();

    if (timeStopMS == UINT_MAX)
    {
        return;
    }

    uint dT = timeStopMS - TIME_MS;

    tim3.StartIT((dT * 2) - 1);             // 10 соответствует 0.1мс. Т.е. если нам нужна 1мс, нужно засылать (100 - 1)
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void TuneTIM(TypeTimer type)
{
    TimerStruct *timer = &timers[type];

    uint timeNearest = NearestTime();

    uint timeNext = TIME_MS + timer->dTms;
    timer->timeNextMS = timeNext;

    if (timeNext < timeNearest)      // Если таймер должен сработать раньше текущего
    {
        StartTIM(timeNext);         // то заводим таймер на наше время
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Enable(TypeTimer type)
{
    timers[type].repeat = true;
    TuneTIM(type);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Disable(TypeTimer type)
{
    timers[type].timeNextMS = UINT_MAX;
    timers[type].repeat = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Timer::IsRun(TypeTimer type)
{
    return TIME_NEXT(type) != UINT_MAX;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::PauseOnTime(uint timeMS)
{
    HAL_Delay(timeMS);
}
