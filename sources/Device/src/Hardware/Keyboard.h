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
    Press,      ///< ������� ������
    Repeat,     ///< �������������� ������
    Release     ///< ���������� ������
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:
    /// ���������� true, ���� button - �������������� ������� [1..5]
    static bool IsFunctionalButton(Key button);
    /// �������� ������ ����������
    /** ����� ������ ���������, �� ���������� ���� ���������� ��������� ���������� releasedButton */
    static void Disable();
    /// �������� ������� �������
    static Key WaitPressingButton();

    static void Enable();

    static pString KeyName(Key control);
};
