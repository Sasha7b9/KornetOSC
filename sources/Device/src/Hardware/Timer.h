#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum TypeTimer
{
    kPressKey,                  ///< Нужно устанавливать, когда приходит нажатие клавиши.
    kShowLevelRShiftA,          ///< Нужно устанавливать, когда изменяется положение ручки смещения канала 1.
    kShowLevelRShiftB,          ///< Нужно устанавливать, когда изменяется положение ручки смещения канала 2.
    kShowLevelTrigLev,          ///< Нужно устанавливать, когда изменяется положение ручки уровня синхронизации
    kENumSignalsInSec,          ///< Для установки количества считываний сигнала в секунду.
    kFlashDisplay,              ///< Таймер для мерцающих участков экрана чёрно-белого дисплея.
    kShowMessages,              ///< Таймер для засекания время показа информационных и предупреждающих сообщений.
    kMenuAutoHide,              ///< Таймер для отсчёта времени скрывания меню.
    kRShiftMarkersAutoHide,     ///< Таймер для отсчёта времени скрывания дополнительных боковых меток.
    kUSB,                       ///< Вспомогательный, для общих нужд.
    kStopSound,                 ///< Выключить звук
    kTemporaryPauseFPGA,        ///< Временная пауза для фиксации сигнала на экране после поворота ручек
    kStrNaviAutoHide,           ///< Прятать строку навигации меню
    kTimerStartP2P,             ///< Таймер для запуска следующего цикла поточечного чтения
    kTimerDisplay,              ///< Таймер на ручную отрисовку экрана
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
    /// Назначает таймеру timer функцию и время срабатывания
    static void Set(TypeTimer type, pFuncVV func, uint dTms);

    static void Enable(TypeTimer type);

    static bool IsRun(TypeTimer type);

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
