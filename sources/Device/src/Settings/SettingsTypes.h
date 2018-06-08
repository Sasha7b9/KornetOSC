#pragma once
#include "defines.h"


struct Range
{
    enum
    {
        _2mV,
        _5mV,
        _10mV,
        _20mV,
        _50mV,
        _100mV,
        _200mV,
        _500mV,
        _1V,
        _2V,
        _5V,
        _10V,
        _20V,
        Size
    };
    Range(uint8 v = _2mV) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
    Range& operator++()
    {
        ++value;
        return *this;
    }
};

struct TBase
{
    enum
    {
        _2ns,
        _5ns,
        _10ns,
        _20ns,
        _50ns,
        _100ns,
        _200ns,
        _500ns,
        _1us,
        _2us,
        _5us,
        _10us,
        _20us,
        _50us,
        _100us,
        _200us,
        _500us,
        _1ms,
        _2ms,
        _5ms,
        _10ms,
        _20ms,
        _50ms,
        _100ms,
        _200ms,
        _500ms,
        _1s,
        _2s,
        _5,
        _10s,
        Size
    };
    TBase(uint8 v = _2ns) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct TrigInput
{
    enum
    {
        Full,
        HF,
        LF
    };
    TrigInput(uint8 v = Full) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

enum Channel
{
    A,
    B,
    Ext,
    Math,
    NumChannels
};


struct MeasSource
{
    enum
    {
        A,
        B,
        A_B
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct TrigPolarity
{
    enum
    {
        Rising,
        Falling
    };
    TrigPolarity(uint8 v = Rising) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

enum Language
{
    RU,
    EN,
    NumLanguages
};

enum ModeDrawSignal
{
    Mode_Lines,
    Mode_Points
};

/// �������� ��������� �������
enum ThicknessSignal
{
    Thickness_1,    ///< ������ �������� ������ �������� ���� �����
    Thickness_3     ///< ������ �������� ������ �������� ��� �����
};

enum Bandwidth
{
    Bandwidth_Full,     ///< ���� ��� �������� ������� � ���� �����, �� ��� ���� ��������� ��������������� ������ �� �������-������-������.
    Bandwidth_20MHz,
    Bandwidth_100MHz,
    Bandwidth_200MHz,
    Bandwidth_350MHz,
    Bandwidth_650MHz,
    Bandwidth_750MHz
};

struct ModeTrig
{
    enum
    {
        Auto,
        Wait,
        Once
    };
    ModeTrig(uint8 v = Auto) : value(v) {};
    uint8 value;
};

/// ��� ����� ��������� � ������-���������� - ����������� ��� �����
enum TesterControl
{
    Control_Voltage,
    Control_Current
};


enum TesterPolarity
{
    Polarity_Positive,
    Polarity_Negative
};

enum TesterStepU
{
    StepU_100mV,
    StepU_500mV
};

enum TesterStepI
{
    StepI_4mA,
    StepI_20mA
};

/// ����� �������� ���������
enum CursCntrl
{
    CursCntrl_1,        ///< ������
    CursCntrl_2,        ///< ������
    CursCntrl_1_2,      ///< ������
    CursCntrl_Disable   ///< �������
};

/// ��� ���������� �� ����������
enum ModeAveraging
{
    Averaging_Accurately,   ///< ��������� �����.
    Averaging_Around        ///< ��������� ��������������.
};

/// ����� ����� ����.
enum Background
{
    Background_Black,
    Background_White
};

/// ��������� ����� ������������� �� �������.
enum TPos
{
    TPos_Left,          ///< �������� � ������ ����.
    TPos_Center,        ///< �������� � ������.
    TPos_Right          ///< �������� � ������� ����.
};

/// ����� ����� �������, � ������� ��� ������.
enum ENumPointsFPGA
{
    FNP_512,
    FNP_1k,
    FNP_2k,
    FNP_4k,
    FNP_8k,
    FPGA_ENUM_POINTS_SIZE
};

/// ��� ������ ��� ������� ������ ������.
enum ModeBtnMemory
{
    ModeBtnMemory_Menu,     ///< ����� ������������ ��������������� �������� ����.
    ModeBtnMemory_Save      ///< ���������� ����������� ������ �� ������.
};

/// ��������.
enum Divider
{
    Divider_1,
    Divider_10
};

/// �������� �������������
enum TrigSource
{
    TrigSource_A,    /// ����� 1
    TrigSource_B,    /// ����� 2
    TrigSource_Ext   /// �������
};

/// ����� ������.
enum ModeWork
{
    ModeWork_Dir,           ///< �������� �����.
    ModeWork_RAM,           ///< � ���� ������ ����� ����������� ��������� ���������� ���������.
    ModeWork_ROM,           ///< � ���� ������ ����� ��������� �� flash-������ ��������� ������������� ����� ����������.
    ModeWork_None           ///< ������������ � ������ Data.c. �����, ����� �������, ��� ������ �� �������� �� �� ����� �����.
};

/// ����� ������ ������ ���������
enum ShowStrNavi
{
    ShowStrNavi_Temp,   ///< ���������� �� ��������� ������
    ShowStrNavi_All,    ///< ������ ����������
    ShowStrNavi_None    ///< ������� �� ����������
};

enum FFTmaxDB
{
    FFTmaxDB_40,
    FFTmaxDB_60,
    FFTmaxDB_80
};

enum FuncModeDraw
{
    FuncModeDraw_Disable,
    FuncModeDraw_Separate,
    FuncModeDraw_Together
};

/// \brief ��� ������������ ��� �������.
/// ���� � ���, ��� ������ ��� �� ��������� ��-�� ������� ������������� ( ? ), ������� �� ������ �������������� �������� ��� ������ �� ��� ������.
enum BalanceADCtype
{
    BalanceADC_Disable,     ///< ������������ ���������.
    BalanceADC_Settings,    ///< ������������ �������� ������������, ������� �������� �������������.
    BalanceADC_Hand         ///< ������������ �������� ������������, �������� �������.
};

/// ��� �������� ���
enum StretchADCtype
{
    StretchADC_Disable,
    StretchADC_Real,
    StretchADC_Hand
};

enum DisplayOrientation
{
    Direct,
    Back
};

/// ����� ������ �� �����.
enum ModeCouple
{
    ModeCouple_DC,      ///< �������� ����.
    ModeCouple_AC,      ///< �������� ����.
    ModeCouple_GND,     ///< ���� �������.
    CoupleSize
};

enum Resistance
{
    Resistance_1Mom,
    Resistance_50Om
};

/// ����� ����� �������.
enum TimeCounting
{
    TimeCounting_100ms,
    TimeCounting_1s,
    TimeCounting_10s
};

/// ������� ����������� ��������� ��� ����� �������.
enum FreqClc
{
    FreqClc_100kHz,
    FreqClc_1MHz,
    FreqClc_10MHz,
    FreqClc_100MHz
};

/// ���������� ��������.
enum NumberPeriods
{
    NumberPeriods_1,
    NumberPeriods_10,
    NumberPeriods_100
};

enum PeakDetMode
{
    PeakDet_Disabled,
    PeakDet_Enabled,
    PeakDet_Average
};

/// ���������� ��������� ��� ������� ������������ � ������������� ��������.
enum ENumMinMax
{
    ENumMinMax_1,
    ENumMinMax_2,
    ENumMinMax_4,
    ENumMinMax_8,
    ENumMinMax_16,
    ENumMinMax_32,
    ENumMinMax_64,
    ENumMinMax_128
};

enum ColorScheme
{
    ColorScheme_WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����
    ColorScheme_BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������
};

/// ���������� ���������� �� ����������.
enum ENumAverage
{
    ENumAverage_1,
    ENumAverage_2,
    ENumAverage_4,
    ENumAverage_8,
    ENumAverage_16,
    ENumAverage_32,
    ENumAverage_64,
    ENumAverage_128,
    ENumAverage_256,
    ENumAverage_512
};

/// ����� �������.
enum StartMode
{
    StartMode_Auto,     ///< ��������������.
    StartMode_Wait,     ///< ������.
    StartMode_Single    ///< �����������.
};

/// ����� �������� ��������.
enum CursLookMode
{
    CursLookMode_None,      ///< ������� �� ������.
    CursLookMode_Voltage,   ///< ������� ������ �� ����������� �������������.
    CursLookMode_Time,      ///< ������� ������ �� �������� �������������.
    CursLookMode_Both       ///< ������� ������ �� �������� � �����������, � ����������� �� ����, ����� ������� ������� ���������.
};

/// ����� ������� ������ �������. ����� �������, �� � ����� ������������ �� �������� ����� ���������.
enum CursActive
{
    CursActive_U,
    CursActive_T,
    CursActive_None
};

/// ������������ ����������� ��������.
enum CursMovement
{
    CursMovement_Pixels,    ///< �� �������� ������
    CursMovement_Percents   ///< �� ���������
};

/// ���������� ����������.
enum ENumAccum
{
    ENumAccum_1,
    ENumAccum_2,
    ENumAccum_4,
    ENumAccum_8,
    ENumAccum_16,
    ENumAccum_32,
    ENumAccum_64,
    ENumAccum_128,
    ENumAccum_Infinity
};

enum ModeAccumulation
{
    ModeAccumulation_NoReset,   /// � ���� ������ ������������ ������ N ���������.
    ModeAccumulation_Reset      /// � ���� ������ ���������� N ��������� � ����� ������������.
};

/// ���������� ����� ��� ������� �����������.
enum ENumSmoothing
{
    ENumSmooth_Disable,
    ENumSmooth_2points,
    ENumSmooth_3points,
    ENumSmooth_4points,
    ENumSmooth_5points,
    ENumSmooth_6points,
    ENumSmooth_7points,
    ENumSmooth_8points,
    ENumSmooth_9points,
    ENumSmooth_10points
};

/// ����������� FPS.
enum ENumSignalsInSec
{
    ENumSignalsInSec_25,
    ENumSignalsInSec_10,
    ENumSignalsInSec_5,
    ENumSignalsInSec_2,
    ENumSignalsInSec_1
};

/// ��� ����� �� ������.
enum TypeGrid
{
    TypeGrid_1,
    TypeGrid_2,
    TypeGrid_3,
    TypeGrid_4,
    TG_Size
};

/// ��� �������� � �������� �� ���������
enum LinkingRShift
{
    LinkingRShift_Voltage,      ///< �������� ��������� � ����������
    LinkingRShift_Position      ///< �������� ��������� � �������
};

/// ����� ����������� �������������� ������� �������� �������� �� ����������.
enum AltMarkers
{
    AM_Hide,        /// ������ �� ��������.
    AM_Show,        /// ������ ��������.
    AM_AutoHide     /// �������� � ������� ����� timeShowLevels.
};

/// ����� ����� ����� ����� ���������� ������� ������ �������� ����.
enum MenuAutoHide
{
    MenuAutoHide_None = 0,   ///< �������.
    MenuAutoHide_5 = 5,   ///< ����� 5 ������.
    MenuAutoHide_10 = 10,  ///< ����� 10 ������.
    MenuAutoHide_15 = 15,  ///< ����� 15 ������.
    MenuAutoHide_30 = 30,  ///< ����� 30 ������.
    MenuAutoHide_60 = 60   ///< ����� 60 ������.
};

enum MeasuresNumber
{
    MN_1,                       ///< 1 ��������� ����� �����.
    MN_2,                       ///< 2 ��������� ����� �����.
    MN_1_5,                     ///< 1 ������ � 5 �����������.
    MN_2_5,                     ///< 2 ������ �� 5 ���������.
    MN_3_5,                     ///< 3 ������ �� 5 ���������.
    MN_6_1,                     ///< 6 ����� �� 1 ���������.
    MN_6_2                      ///< 6 ����� �� 2 ���������.
};

/// ������� �� ������� ��� ������ ���������.
enum ModeViewSignals
{
    ModeViewSignals_AsIs,       ///< ���������� ������� ��� ����.
    ModeViewSignals_Compress    ///< ������� ����� � ���������.
};

/// ��� ������� ��� ������ �������������.
enum SampleType
{
    SampleType_Real,    ///< �������� ����� - � ���������� ��������� ������ ������� ��������� �����, ������ �� ��������������.
    SampleType_Equal    ///< ������������� - ������ �������� �� ��������� ������, ���������� �� �������������.
};

/// ������� ��/���.
enum FunctionTime
{
    FunctionTime_Time,
    FunctionTime_ShiftInMemory
};

/// ��� �������� � �������� �� �����������
enum LinkingTShift
{
    LinkingTShift_Time,     ///< �������� ��������� � �������
    LinkingTShift_Position  ///< �������� ��������� � �������
};

enum TrigModeFind
{
    TrigModeFind_Hand,      ///< ������� ������������� ��������������� ������� ��� ������������� - ����������� ��������� ������.
    TrigModeFind_Auto       ///< ���������� ������ ������������� ������������ ������������� ����� ������� ������ ���������� �������.
};

enum CalibratorMode
{
    Calibrator_Freq,
    Calibrator_DC,
    Calibrator_GND
};

/// ����� ����������.
enum CalibrationMode
{
    CalibrationMode_x1,
    CalibrationMode_x10,
    CalibrationMode_Disable
};

enum ScaleFFT
{
    ScaleFFT_Log,           ///< ��� �������� �������� ��������������� ����� ������ �������.
    ScaleFFT_Linear         ///< ��� �������� �������� �������� ����� ������ �������.
};

enum SourceFFT
{
    SourceFFT_ChannelA,
    SourceFFT_ChannelB,
    SourceFFT_Both
};

enum WindowFFT
{
    WindowFFT_Rectangle,
    WindowFFT_Hamming,
    WindowFFT_Blackman,
    WindowFFT_Hann
};

enum Function
{
    Function_Sum,
    Function_Mul
};

enum ModeRegSet
{
    ModeRegSet_Range,
    ModeRegSet_RShift
};

/// ����� ������������ ������.
enum FileNamingMode
{
    FileNamingMode_Mask,        ///< ��������� �� �����.
    FileNamingMode_Manually     ///< ��������� �������.
};

/// ��� ��������� ������ �� ������.
enum ModeSaveSignal
{
    ModeSaveSignal_BMP,
    ModeSaveSignal_TXT
};

/// ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
enum ModeShowIntMem
{
    ModeShowIntMem_Direct,  ///< ���������� ������ ��������� �������.
    ModeShowIntMem_Saved,   ///< ���������� ���������� ������.
    ModeShowIntMem_Both     ///< ���������� ��� �������.
};

const char *NameRange(Range range);
const char *NameTBase(TBase tBase);
