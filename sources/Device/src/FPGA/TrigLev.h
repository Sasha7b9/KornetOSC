#pragma once
#include "defines.h"


class TrigLev
{

friend class FPGA;

public:
    static const int MIN = 20;
    static const int MAX = 980;
    static const int ZERO = 500;
    /// Возвращает true в случае наличия синхроимпульса
    static bool SyncPulse();

private:
    /// Установленное в true значение означает, что нужно выводить значок синхроимпульса
    static bool pulse;
    /// Время принудительного запуска
    static uint timeSwitchingTrig;
};
