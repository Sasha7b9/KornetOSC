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

/// ����� �������� ���������
struct CursCntrl
{
    enum
    {
        _1,        ///< ������
        _2,        ///< ������
        _1_2,      ///< ������
        Disable    ///< �������
    };
    COMMON_ENUM;
};

/// ��� ���������� �� ����������
struct ModeAveraging
{
    enum
    {
        Accurately,   ///< ��������� �����.
        Around        ///< ��������� ��������������.
    };
    ModeAveraging(uint8 v = Accurately) : value(v) {};
    COMMON_ENUM;
};

/// ����� ����� ����.
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

/// ��������� ����� ������������� �� �������.
struct TPos
{
    enum
    {
        Left,          ///< �������� � ������ ����.
        Center,        ///< �������� � ������.
        Right          ///< �������� � ������� ����.
    };
    COMMON_ENUM;
};

/// ��� ������ ��� ������� ������ ������.
struct ModeBtnMemory
{
    enum
    {
        Menu,     ///< ����� ������������ ��������������� �������� ����.
        Save      ///< ���������� ����������� ������ �� ������.
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

/// \brief ��� ������������ ��� �������.
/// ���� � ���, ��� ������ ��� �� ��������� ��-�� ������� ������������� ( ? ), ������� �� ������ �������������� �������� ��� ������ �� ��� ������.
struct BalanceADC
{
    enum
    {
        Disable,     ///< ������������ ���������.
        Settings,    ///< ������������ �������� ������������, ������� �������� �������������.
        Hand         ///< ������������ �������� ������������, �������� �������.
    };
    COMMON_ENUM;
};

/// ��� �������� ���
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

/// ����� ����� �������.
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

/// ������� ����������� ��������� ��� ����� �������.
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

/// ���������� ��������.
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
