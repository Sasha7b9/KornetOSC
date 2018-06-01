#pragma once

enum Control
{
    B_None,
    B_Function,
    B_Measures,
    B_Memory,
    B_Service,
    B_ChannelA,
    B_ChannelB,
    B_Time,         //
    B_Start,
    B_Trig,         //
    B_Menu,
    B_RangeMoreA,
    B_RangeLessA,
    B_RShiftMoreA,
    B_RShiftLessA,
    B_RangeMoreB,
    B_RangeLessB,
    B_RShiftMoreB,
    B_RShiftLessB,
    B_TBaseMore,
    B_TBaseLess,
    B_TShiftMore,   //
    B_TShiftLess,   //
    B_TrigLevMore,     //
    B_TrigLevLess,
    B_Left,
    B_Right,
    B_Up,
    B_Down,
    B_Enter,
    B_1,
    B_2,
    B_3,
    B_4,
    B_5,
    NumButtons
};

enum TypePress
{
    Press,      ///< Нажатие кнопки
    Repeat,     ///< Автоматический повтор
    Release     ///< Отпускание кнопки
};

/// Хранит код органа управления и его состояние - если pressed == true, то кнопка находится в нажатом состоянии
struct StructControl
{
    Control key;
    TypePress    typePress;
};
