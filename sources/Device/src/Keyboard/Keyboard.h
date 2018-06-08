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

    bool IsFunctional()
    {
        return code >= F1 && code <= F5;
    }

    pString Name();

    enum
    {
        None = 0,
        Function = 1,
        Measures = 2,
        Memory = 3,
        Service = 4,
        ChannelA = 5,
        ChannelB = 6,
        Time = 7,
        Start = 8,
        Trig = 9,
        Display = 10,
        RangeMoreA = 11,
        RangeLessA = 12,
        RShiftMoreA = 13,
        RShiftLessA = 14,
        RangeMoreB = 15,
        RangeLessB = 16,
        RShiftMoreB = 17,
        RShiftLessB = 18,
        TBaseMore = 19,
        TBaseLess = 20,
        TShiftMore = 21,
        TShiftLess = 22,
        TrigLevMore = 23,
        TrigLevLess = 24,
        Left = 25,
        Right = 26,
        Up = 27,
        Down = 28,
        Enter = 29,
        F1 = 30,
        F2 = 31,
        F3 = 32,
        F4 = 33,
        F5 = 34,
        NumButtons
    };
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TypePress
{
public:
    TypePress(uint8 value = None) : type(value)
    {
    };

    uint8 type;

    bool Is(uint8 value)
    {
        return type == value;
    }

    pString ToString();

    enum
    {
        Press,      ///< Нажатие кнопки
        Repeat,     ///< Автоматический повтор
        Release,    ///< Отпускание кнопки
        Long,       ///< "Длинное" нажатие кнопки
        None
    };
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct KeyEvent
{
    KeyEvent(Key k = Key::None, TypePress t = TypePress::None) : key(k), type(t)
    {
    };
    Key key;
    TypePress type;
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
};
