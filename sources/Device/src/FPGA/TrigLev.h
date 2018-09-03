#pragma once
#include "defines.h"


class Trig
{

friend class FPGA;

public:
    static const int MIN = 20;
    static const int MAX = 980;
    static const int ZERO = 500;
    /// Возвращает true в случае наличия синхроимпульса
    static bool SyncPulse();

    /// Источник синхронизации
    struct Source
    {
        enum E
        {
            A,    /// Канал 1
            B,    /// Канал 2
            Ext   /// Внешняя
        } value;
        operator uint8() const { return (uint8)value; }
    };

    /// Режим запуска.
    struct StartMode
    {
        enum E
        {
            Auto,     ///< Автоматический.
            Wait,     ///< Ждущий.
            Single    ///< Однократный.
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct ModeFind
    {
        enum E
        {
            Hand,      ///< Уровень синхронизации устанавливается вручную или автоматически - однократным нажажтием кнопки.
            Auto       ///< Подстройки уровня синхронизации производится автоматически после каждого нового считанного сигнала.
        } value;
        operator uint8() const { return (uint8)value; };
    };

private:
    /// Установленное в true значение означает, что нужно выводить значок синхроимпульса
    static bool pulse;
    /// Время принудительного запуска
    static uint timeSwitchingTrig;
};
