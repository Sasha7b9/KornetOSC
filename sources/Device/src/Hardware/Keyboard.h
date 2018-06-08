#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Key
{
public:
    Key(uint8 value = None) : code(value)
    {
    };
    uint8 code;

    bool Is(uint8 value)
    {
        return code == value;
    }

    enum
    {
        None,
        Function,
        Measures,
        Memory,
        Service,
        ChannelA,
        ChannelB,
        Time,         //
        Start,
        Trig,         //
        Display,
        RangeMoreA,
        RangeLessA,
        RShiftMoreA,
        RShiftLessA,
        RangeMoreB,
        RangeLessB,
        RShiftMoreB,
        RShiftLessB,
        TBaseMore,
        TBaseLess,
        TShiftMore,   //
        TShiftLess,   //
        TrigLevMore,     //
        TrigLevLess,
        Left,
        Right,
        Up,
        Down,
        Enter,
        F1,
        F2,
        F3,
        F4,
        F5,
        NumButtons
    };
};

enum TypePress
{
    Press,      ///< Нажатие кнопки
    Repeat,     ///< Автоматический повтор
    Release     ///< Отпускание кнопки
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:
    /// Возвращает true, если button - функциональная клавиша [1..5]
    static bool IsFunctionalButton(Key button);
    /// Отлючить панель управления
    /** Когда панель отключена, то происходит лишь обновление состояния переменной releasedButton */
    static void Disable();
    /// Ожидание нажатия клавиши
    static Key WaitPressingButton();

    static void Enable();

    static pString KeyName(Key control);
};
