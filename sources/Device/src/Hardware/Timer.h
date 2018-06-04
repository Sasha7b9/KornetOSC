#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:

    static void Init();

private:
};


/// Запускает счётчик для измерения малых отрезков времени (тиков и микросекунд). Счётчика хватает где-то на 30 секунд.
#define START_MULTI_MEASUREMENT()   { TIM2->CR1 &= (uint)~TIM_CR1_CEN; TIM2->CNT = 0; TIM2->CR1 |= TIM_CR1_CEN; }
/// Количество прошедших тактов с последнего вызова START_MULTI_MEASUREMENT
#define TIME_TICKS  (TIM2->CNT)
/// Количество прошедших микросекунд с последнего вызоыва START_MULTI_MEASUREMENT
#define TIME_US     (TIME_TICKS / 90)
/// Количество миллисекунд, прошедших с начала работы программы
#define TIME_MS     HAL_GetTick()

#define PAUSE_ON_TICKS(x)   { uint time = TIME_TICKS; while(time + (x) > TIME_TICKS) {}; }
#define PAUSE_ON_US(x)      { uint time = TIME_US; while (TIME_US - time < (x)) {}; }
#define PAUSE_ON_MS(x)      { uint time = TIME_MS; while (TIME_MS - time < (x)) {}; }
