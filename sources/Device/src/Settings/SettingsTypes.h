#pragma once
#include "defines.h"
#include "SettingsChannel.h"


#define COMMON_ENUM     uint8 value; operator uint8() const { return value; }; operator uint8() { return value; }


/// ��� ����� ��������� � ������-���������� - ����������� ��� �����
struct TesterControl
{
    enum
    {
        Voltage,
        Current
    };
    COMMON_ENUM;
};


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

/// ����� ������ ������ ���������
struct ShowStrNavi
{
    enum
    {
        Temp,   ///< ���������� �� ��������� ������
        All,    ///< ������ ����������
        None    ///< ������� �� ����������
    };
    COMMON_ENUM;
};

struct FFTmaxDB
{
    enum
    {
        _40,
        _60,
        _80
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

struct DisplayOrientation
{
    enum
    {
        Direct,
        Back
    };
    COMMON_ENUM;
};

/// ����� ������ �� �����.
struct ModeCouple
{
    enum
    {
        DC,      ///< �������� ����
        AC,      ///< �������� ����
        GND,     ///< ���� �������.
        Size
    };
    COMMON_ENUM;
    ModeCouple(uint v = 0) : value((uint8)v) {};
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

/// ���������� ��������� ��� ������� ������������ � ������������� ��������.
struct ENumMinMax
{
    enum
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128
    };
    COMMON_ENUM;
};

struct ColorScheme
{
    enum
    {
        WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����
        BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������
    };
    COMMON_ENUM;
};

/// ���������� ���������� �� ����������.
struct ENumAverage
{
    enum
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128,
        _256,
        _512
    };
    COMMON_ENUM;
};

/// ����� �������.
struct StartMode
{
    enum
    {
        Auto,     ///< ��������������.
        Wait,     ///< ������.
        Single    ///< �����������.
    };
    COMMON_ENUM;
};

/// ����� �������� ��������.
struct CursLookMode
{
    enum
    {
        None,      ///< ������� �� ������.
        Voltage,   ///< ������� ������ �� ����������� �������������.
        Time,      ///< ������� ������ �� �������� �������������.
        Both       ///< ������� ������ �� �������� � �����������, � ����������� �� ����, ����� ������� ������� ���������.
    };
    COMMON_ENUM;
};

/// ����� ������� ������ �������. ����� �������, �� � ����� ������������ �� �������� ����� ���������.
struct CursActive
{
    enum
    {
        U,
        T,
        None
    };
    COMMON_ENUM;
    CursActive(uint8 v = None) : value(v) {};
};

/// ������������ ����������� ��������.
struct CursMovement
{
    enum
    {
        Pixels,    ///< �� �������� ������
        Percents   ///< �� ���������
    };
    COMMON_ENUM;
};

/// ���������� ����������.
struct ENumAccum
{
    enum
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128,
        _Infinity
    };
    COMMON_ENUM;
};

struct ModeAccumulation
{
    enum
    {
        NoReset,   /// � ���� ������ ������������ ������ N ���������.
        Reset      /// � ���� ������ ���������� N ��������� � ����� ������������.
    };
    COMMON_ENUM;
};

/// ���������� ����� ��� ������� �����������.
struct ENumSmoothing
{
    enum
    {
        Disable,
        _2points,
        _3points,
        _4points,
        _5points,
        _6points,
        _7points,
        _8points,
        _9points,
        _10points
    };
    COMMON_ENUM;
};

/// ����������� FPS.
struct ENumSignalsInSec
{
    enum
    {
        _25,
        _10,
        _5,
        _2,
        _1
    };
    ENumSignalsInSec(uint8 v = _25) : value(v) {};
    COMMON_ENUM;
};

/// ��� ����� �� ������.
struct TypeGrid
{
    enum
    {
        _1,
        _2,
        _3,
        _4,
        Size
    };
    COMMON_ENUM;
};

/// ��� �������� � �������� �� ���������
struct LinkingRShift
{
    enum
    {
        Voltage,      ///< �������� ��������� � ����������
        Position      ///< �������� ��������� � �������
    };
    COMMON_ENUM;
};

/// ����� ����������� �������������� ������� �������� �������� �� ����������.
struct AltMarkers
{
    enum
    {
        Hide,        /// ������ �� ��������.
        Show,        /// ������ ��������.
        AutoHide     /// �������� � ������� ����� timeShowLevels.
    };
    COMMON_ENUM;
};

/// ����� ����� ����� ����� ���������� ������� ������ �������� ����.
struct MenuAutoHide
{
    enum
    {
        None = 0,   ///< �������.
        _5 = 5,   ///< ����� 5 ������.
        _10 = 10,  ///< ����� 10 ������.
        _15 = 15,  ///< ����� 15 ������.
        _30 = 30,  ///< ����� 30 ������.
        _60 = 60   ///< ����� 60 ������.
    };
    COMMON_ENUM;
};

struct MeasuresNumber
{
    enum
    {
        _1,                       ///< 1 ��������� ����� �����.
        _2,                       ///< 2 ��������� ����� �����.
        _1_5,                     ///< 1 ������ � 5 �����������.
        _2_5,                     ///< 2 ������ �� 5 ���������.
        _3_5,                     ///< 3 ������ �� 5 ���������.
        _6_1,                     ///< 6 ����� �� 1 ���������.
        _6_2                      ///< 6 ����� �� 2 ���������.
    };
    COMMON_ENUM;
};

/// ������� �� ������� ��� ������ ���������.
struct ModeViewSignals
{
    enum
    {
        AsIs,       ///< ���������� ������� ��� ����.
        Compress    ///< ������� ����� � ���������.
    };
    COMMON_ENUM;
};

/// ��� ������� ��� ������ �������������.
struct SampleType
{
    enum
    {
        Real,    ///< �������� ����� - � ���������� ��������� ������ ������� ��������� �����, ������ �� ��������������.
        Equal    ///< ������������� - ������ �������� �� ��������� ������, ���������� �� �������������.
    };
    COMMON_ENUM;
    SampleType(uint8 v = Real) : value(v) {};
};

/// ������� ��/���.
struct FunctionTime
{
    enum
    {
        Time,
        ShiftInMemory
    };
    COMMON_ENUM;
};

/// ��� �������� � �������� �� �����������
struct LinkingTShift
{
    enum
    {
        Time,     ///< �������� ��������� � �������
        Position  ///< �������� ��������� � �������
    };
    COMMON_ENUM;
};

struct TrigModeFind
{
    enum
    {
        Hand,      ///< ������� ������������� ��������������� ������� ��� ������������� - ����������� ��������� ������.
        Auto       ///< ���������� ������ ������������� ������������ ������������� ����� ������� ������ ���������� �������.
    };
    COMMON_ENUM;
};

struct CalibratorMode
{
    enum
    {
        Freq,
        DC,
        GND
    };
    COMMON_ENUM;
};

/// ����� ����������.
struct CalibrationMode
{
    enum
    {
        x1,
        x10,
        Disable
    };
    COMMON_ENUM;
};

struct ScaleFFT
{
    enum
    {
        Log,           ///< ��� �������� �������� ��������������� ����� ������ �������.
        Linear         ///< ��� �������� �������� �������� ����� ������ �������.
    };
    COMMON_ENUM;
};

struct SourceFFT
{
    enum
    {
        A,
        B,
        Both
    };
    COMMON_ENUM;
};

struct WindowFFT
{
    enum
    {
        Rectangle,
        Hamming,
        Blackman,
        Hann
    };
    COMMON_ENUM;
};

struct Function
{
    enum
    {
        Sum,
        Mul
    };
    COMMON_ENUM;
};

struct ModeRegSet
{
    enum
    {
        Range,
        RShift
    };
    COMMON_ENUM;
};

/// ����� ������������ ������.
struct FileNamingMode
{
    enum
    {
        Mask,        ///< ��������� �� �����.
        Manually     ///< ��������� �������.
    };
    COMMON_ENUM;
};

/// ��� ��������� ������ �� ������.
struct ModeSaveSignal
{
    enum
    {
        BMP,
        TXT
    };
    COMMON_ENUM;
};

/// ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
struct ModeShowIntMem
{
    enum
    {
        Direct,  ///< ���������� ������ ��������� �������.
        Saved,   ///< ���������� ���������� ������.
        Both     ///< ���������� ��� �������.
    };
    COMMON_ENUM;
};
