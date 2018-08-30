#pragma once
#include "defines.h"
#include "DisplayTypes.h"
#include "Keyboard/Keyboard.h"
#include "Settings/SettingsDisplay.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BACKGROUND                  (set.disp_background)
#define BACKGROUND_BLACK            (BACKGROUND == Display::Background::Black)

#define SHOW_STRING_NAVI            (set.disp_showStringNavigation)
#define SHOW_STRING_NAVI_TEMP       (SHOW_STRING_NAVI == Display::ShowStrNavi::Temp)
#define SHOW_STRING_NAVI_ALL        (SHOW_STRING_NAVI == Display::ShowStrNavi::All)

#define MODE_DRAW_SIGNAL            (set.disp_modeDrawSignal)
#define MODE_DRAW_SIGNAL_IS_LINES   (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Lines)
#define MODE_DRAW_SIGNAL_IS_POINTS  (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Points)

#define THICKNESS_SIGNAL            (set.disp_thickness)
#define THICKNESS_SIGNAL_IS_3       (THICKNESS_SIGNAL == Display::ThicknessSignal::_3)

#define ENUM_MIN_MAX                (set.disp_ENumMinMax)
#define MIN_MAX_ENABLED             (ENUM_MIN_MAX != Display::ENumMinMax::_1)
#define NUM_MIN_MAX                 (1 << (int)ENUM_MIN_MAX)                /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LogEntity
{
    friend class Log;
};

#define DISPLAY_SHOW_WARNING(warn)  Display::ShowWarning(warn)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// C��������, ��������� �� �����
struct Warning
{
    enum E
    {
        LimitChan1_Volts,               ///< ������ �������� �� ����������� ������� ������.
        LimitChan2_Volts,               ///< ������ �������� �� ���������� ������� ������.
        LimitSweep_Time,                ///< ������ �������� �� �������.
        EnabledPeakDet,                 ///< ������� ������� ��������.
        LimitChan1_RShift,              ///< ������ �������� �� ���������� ������� ������.
        LimitChan2_RShift,              ///< ������ �������� �� ���������� ������� ������.
        LimitSweep_Level,               ///< ������ ������ �������������.
        LimitSweep_TShift,              ///< ������ �������� �� �������.
        TooSmallSweepForPeakDet,        ///< ������� ������� �������� ��� �������� ���������.
        TooFastScanForRecorder,         ///< ������� ������� �������� ��� ����������� ������.
        FileIsSaved,                    ///< ���� ������� �� ������.
        SignalIsSaved,                  ///< ������ ������� � ���.
        SignalIsDeleted,                ///< �� ���� ����� ������.
        MenuDebugEnabled,               ///< �������� ���� �������.
        TimeNotSet,                     ///< ����� �� �����������.
        SignalNotFound,                 ///< ������ �� ������ (���������).
        SetTPosToLeft,                  ///< ������������.
        NeedRebootDevice,               ///< ��������� ������������.
        ImpossibleEnableMathFunction,   ///< ���������� �������� �������������� �������.
        ImpossibleEnableFFT,            ///< ���������� �������� ���������� ���.
        WrongFileSystem,                ///< ���������� ���������� ������.
        WrongModePeackDet,              ///< ���������� �������� ������� ��������.
        DisableChannelB,                ///< ��������� ��������� ����� 2.
        TooLongMemory,                  ///< ��������� � ������������� ��������� ������ 32�.
        NoPeakDet32k,                   ///< ������� �������� �� �������� ��� ����� ������ 32�.
        NoPeakDet16k,                   ///< ������� �������� �� �������� ��� ����� ������ 16�.
        Warn50Ohms,                     ///< �������������� �� ����������� �������� ������ �� 50 ����.
        WarnNeedForFlashDrive,          ///< ��������� ������������ ������.
        FirmwareSaved,                  ///< �������� ��������� �� ������.
        FullyCompletedOTP,              ///< 
        Number
    } value;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
    friend class LogEntity;
public:
    
    static const int HEIGHT = 240;

    static const int WIDTH = 320;
    /// ��� ������� ����� �������� ��� �������� ����� ������ ������������� ��� ��������� ��������� ��������������� ��������
    static void RotateTrigLev();

    static void Init();

    static void Update();

    static void SetKey(Key key);

    static void RemoveAddDrawFunction();

    static void ShowWarning(Warning::E warning);
    /// @brief ���������� ������� � ����� ��������� ������.
    /// @details �������� ��� ��������.
    /// 1. DrawMode_Hand - � ���� ������ ����� ���������� ������� func(), ������������ �������������, � �������� 25 ��� � �������.
    /// ������������ � �������, ����� �� ����������� ������� ����.
    /// 2. DrawMode::Auto � func == 0 - � ���� ������ ����� ����������� ������� Update() � ������� �����.
    /// 3. DrawMode::Auto � func != 0 - � ���� ������ ����� ����������� ������� func(), ������������ �������������, �� � ����
    /// �������� �����, ������ ���������� �� Update() ������ Update().
    static void SetDrawMode(DrawMode mode, pFuncVV func);

    static void FuncOnWaitStart(const char *text, bool eraseBackground);

    static void FuncOnWaitStop();

    static void SetAddDrawFunction(pFuncVV func);

    static void ChangedRShiftMarkers(bool active);

    static void Clear();

private:

    static void UpdateTester();

    static void DrawDataTester(int numStep, int x, int y);

    static Key key;

public:

    /// ����� ����� ����.
    struct Background
    {
        enum E
        {
            Black,
            White
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct ModeDrawSignal
    {
        enum E
        {
            Lines,
            Points
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ������� ��������� �������
    struct ThicknessSignal
    {
        enum E
        {
            _1,         ///< ������ �������� ������ �������� ���� �����
            _3          ///< ������ �������� ������ �������� ��� �����
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ����� ������ ������ ���������
    struct ShowStrNavi
    {
        enum E
        {
            Temp,   ///< ���������� �� ��������� ������
            All,    ///< ������ ����������
            None    ///< ������� �� ����������
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ���������� ��������� ��� ������� ������������ � ������������� ��������.
    struct ENumMinMax
    {
        enum E
        {
            _1,
            _2,
            _4,
            _8,
            _16,
            _32,
            _64,
            _128
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ��� ���������� �� ����������
    struct ModeAveraging
    {
        enum E
        {
            Accurately,   ///< ��������� �����.
            Around        ///< ��������� ��������������.
        } value;
        ModeAveraging(E v) : value(v) {};
        operator uint8() const  { return (uint8)value; };
    };

    struct Orientation
    {
        enum E
        {
            Direct,
            Back
        } value;
    };
    /// ����� ����������� �������������� ������� �������� �������� �� ����������.
    struct AltMarkers
    {
        enum E
        {
            Hide,        /// ������ �� ��������.
            Show,        /// ������ ��������.
            AutoHide     /// �������� � ������� ����� timeShowLevels.
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ��� �������� � �������� �� ���������
    struct LinkingRShift
    {
        enum E
        {
            Voltage,      ///< �������� ��������� � ����������
            Position      ///< �������� ��������� � �������
        } value;
    };


    static void SetOrientation(Orientation orientation);
    /// ���������� ����� ����������
    static ModeAveraging GetModeAveraging();

};
