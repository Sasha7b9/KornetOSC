#pragma once

enum Control
{
    K_None = 0,
    K_Function = 1,
    K_Measures = 2,
    K_Memory = 3,
    K_Service = 4,
    K_ChannelA = 4,
    K_ChannelB = 6,
    K_Time = 7,
    K_Start = 8,
    K_Trig = 9,
    K_Display = 10,
    K_RangeMoreA = 11,
    B_RangeLessA = 12,
    B_RShiftMoreA = 13,
    B_RShiftLessA = 14,
    B_RangeMoreB = 15,
    B_RangeLessB = 16,
    B_RShiftMoreB = 17,
    B_RShiftLessB = 18,
    B_TBaseMore = 19,
    B_TBaseLess = 20,
    B_TShiftMore = 21,
    B_TShiftLess = 22,
    B_TrigLevMore = 23,
    B_TrigLevLess = 24,
    B_Left = 25,
    B_Right = 26,
    B_Up = 27,
    B_Down = 28,
    B_Enter = 29,
    B_1 = 30,
    B_2 = 31,
    B_3 = 32,
    B_4 = 33,
    B_5 = 34,
    NumButtons
};

enum TypePress
{
    Press,
    Repeat,
    Release
};

/// ������ ��� ������ ���������� � ��� ��������
struct StructControl
{
    Control     key;
    TypePress   typePress;
};


bool IsRepeatable(Control control);
