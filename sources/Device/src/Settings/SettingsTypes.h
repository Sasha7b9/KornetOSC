#pragma once
#include "defines.h"
#include "SettingsChannel.h"


#define COMMON_ENUM     uint8 value; operator uint8() const { return value; }; operator uint8() { return value; }


struct FuncModeDraw
{
    enum
    {
        Disable,
        Separate,
        Together
    };
    COMMON_ENUM;
};

/// \brief Тип балансировки АЦП каналов.
/// Дело в том, что уровни АЦП не совпадают из-за отличия характеристик ( ? ), поэтому мы вводим дополнительное смещение для одного из АЦП канала.
struct BalanceADC
{
    enum
    {
        Disable,     ///< Балансировка выключена.
        Settings,    ///< Используются значения балансировки, которые получены автоматически.
        Hand         ///< Используются значения балансировки, заданные вручную.
    };
    COMMON_ENUM;
};

/// Тип растяжки АЦП
struct StretchADC
{
    enum
    {
        Disable,
        Real,
        Hand
    };
    COMMON_ENUM;
};

struct Resistance
{
    enum
    {
        _1Mom,
        _50Om
    };
    COMMON_ENUM;
};

/// Время счёта периода.
struct TimeCounting
{
    enum
    {
        _100ms,
        _1s,
        _10s
    };
    COMMON_ENUM;
};

/// Частота заполняющих импульсов для счёта частоты.
struct FreqClc
{
    enum
    {
        _100kHz,
        _1MHz,
        _10MHz,
        _100MHz
    };
    COMMON_ENUM;
};

/// Количество периодов.
struct NumberPeriods
{
    enum
    {
        _1,
        _10,
        _100
    };
    COMMON_ENUM;
};
