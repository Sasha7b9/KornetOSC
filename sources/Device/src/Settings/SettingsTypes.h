#pragma once
#include "defines.h"
#include "SettingsChannel.h"


#define COMMON_ENUM     uint8 value; operator uint8() const { return value; }; operator uint8() { return value; }


struct TesterPolarity
{
    enum
    {
        Positive,
        Negative
    };
    COMMON_ENUM;
};

struct TesterStepU
{
    enum
    {
        _100mV,
        _500mV
    };
    COMMON_ENUM;
};

struct TesterStepI
{
    enum
    {
        _4mA,
        _20mA
    };
    COMMON_ENUM
};

/// Каким курсором управлять
struct CursCntrl
{
    enum
    {
        _1,        ///< первым
        _2,        ///< вторым
        _1_2,      ///< обоими
        Disable    ///< никаким
    };
    COMMON_ENUM;
};

/// Тип усреднений по измерениям
struct ModeAveraging
{
    enum
    {
        Accurately,   ///< Усреднять точно.
        Around        ///< Усреднять приблизительно.
    };
    ModeAveraging(uint8 v = Accurately) : value(v) {};
    COMMON_ENUM;
};

/// Выбор цвета фона.
struct Background
{
    enum
    {
        Black,
        White
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

/// Положение точки синхронизация на сигнале.
struct TPos
{
    enum
    {
        Left,          ///< Привязка к левому краю.
        Center,        ///< Привязка к центру.
        Right          ///< Привязка к правому краю.
    };
    COMMON_ENUM;
};

/// Что делать при нажатии кнопки ПАМЯТЬ.
struct ModeBtnMemory
{
    enum
    {
        Menu,     ///< Будет открывааться соответствующая страница меню.
        Save      ///< Сохранение содержимого экрана на флешку.
    };
    COMMON_ENUM;
};

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
