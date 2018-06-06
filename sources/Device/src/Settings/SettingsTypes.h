#pragma once


enum Range
{
    Range_2mV,
    Range_5mV,
    Range_10mV,
    Range_20mV,
    Range_50mV,
    Range_100mV,
    Range_200mV,
    Range_500mV,
    Range_1V,
    Range_2V,
    Range_5V,
    Range_10V,
    Range_20V,
    RangeSize
};

enum TBase
{
    TBase_2ns,
    TBase_5ns,
    TBase_10ns,
    TBase_20ns,
    TBase_50ns,
    TBase_100ns,
    TBase_200ns,
    TBase_500ns,
    TBase_1us,
    TBase_2us,
    TBase_5us,
    TBase_10us,
    TBase_20us,
    TBase_50us,
    TBase_100us,
    TBase_200us,
    TBase_500us,
    TBase_1ms,
    TBase_2ms,
    TBase_5ms,
    TBase_10ms,
    TBase_20ms,
    TBase_50ms,
    TBase_100ms,
    TBase_200ms,
    TBase_500ms,
    TBase_1s,
    TBase_2s,
    TBase_5,
    TBase_10s,
    TBaseSize
};

enum TrigInput
{
    TrigInput_Full,
    TrigInput_HF,
    TrigInput_LF
};

enum Channel
{
    A,
    B,
    Ext,
    Math,
    NumChannels
};

enum TrigPolarity
{
    Polarity_Rising,
    Polarity_Falling
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

enum ModeTrig
{
    ModeTrig_Auto,
    ModeTrig_Wait,
    ModeTrig_Once
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

const char *NameRange(Range range);
const char *NameTBase(TBase tBase);
