#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Utils/Measures.h"
#include "SettingsTypes.h"
#include "Menu/MenuItems.h"
#include "SettingsChannel.h"
#include "SettingsDisplay.h"
#include "SettingsTime.h"
#include "SettingsMath.h"
#include "SettingsMemory.h"
#include "SettingsTrig.h"
#include "SettingsDebug.h"
#include "SettingsNRST.h"
#include "SettingsService.h"
#include "SettingsMeasures.h"
#include "SettingsCursors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TESTER_NUM_POINTS               (240)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IN_RANDOMIZE_MODE               (SET_TBASE < TBase::_100ns)
#define CURRENT_PAGE                    (set.menu_currentPage)

#define TRIG_MODE                       (set.trig_mode)

#define TESTER_CONTROL                  (set.test_control)
#define TESTER_CONTROL_IS_U             (TESTER_CONTROL == Control_Voltage)
#define TESTER_POLARITY                 (set.test_polarity)
#define TESTER_POLARITY_IS_POSITITVE    (TESTER_POLARITY == Polarity_Positive)
#define TESTER_STEP_U                   (set.test_stepU)
#define TESTER_STEP_I                   (set.test_stepI)
#define TESTER_NUM_SMOOTH               (set.test_smooth)

#define MENU_IS_SHOWN                   (set.menu_show)


/// ���������� ������� ��������� ������ �� �������� namePage.
#define MENU_POS_ACT_ITEM(name)     (set.menu_posActItem[name])
/// ������� �����������
#define MENU_CURRENT_SUBPAGE(name)  (set.menu_currentSubPage[name])

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings
{
public:
    static void Load(bool _default = false);
    static void Save();
    static void Reset();
    /// �������� ����� �� �������� �� ���������
    static void ResetColors();

    uint                size;                               ///< ������ ������ ��������� � ������
    uint                crc32;                              ///< \brief ����������� ����� ������ ��������� � ����������� � ��� �����������. ����������� ����� 

    // ���� �������
                                                            ///< ����������� �� ������� �����, ���������� �� ���� �����
    ModeDrawSignal      disp_modeDrawSignal;
    ThicknessSignal     disp_thickness;                     ///< ������� �����, ������� �������� ������
    Background          disp_background;                    ///< ���� ����.
    ShowStrNavi         disp_showStringNavigation;          ///< ����� ������ ������ ��������� ����.
    ENumMinMax          disp_ENumMinMax;                    ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    ModeAveraging       disp_modeAveraging;                 ///< ��� ���������� �� ����������.
    ENumAverage         disp_ENumAverage;                   ///< ����� ���������� �������.
    ENumAccum           disp_ENumAccum;                     ///< ����� ���������� ������� �� ������.
    ModeAccumulation    disp_modeAccumulation;              ///< ����� ���������� ��������.
    ENumSmoothing       disp_ENumSmoothing;                 ///< ������������ ���������� ����� ��� ����������� �������.
    ENumSignalsInSec    disp_ENumSignalsInSec;              ///< ������������ ����� ���������� ������� � �������.
    TypeGrid            disp_typeGrid;                      ///< ��� �����
    int16               disp_brightnessGrid;                ///< ������� ����� �� 0 �� 100.
    LinkingRShift       disp_linkingRShift;                 ///< ��� �������� � �������� �� ���������.
    int16               disp_brightness;                    ///< ������� �������.
    int16               disp_timeShowLevels;                ///< �����, � ������� �������� ����� ���������� ������ ��������.
    int16               disp_timeMessages;                  ///< ����� � ��������, �� ������� ��������� ������� �� �����.
    AltMarkers          disp_altMarkers;                    ///< ����� ����������� �������������� ������� �������� ��������.
    MenuAutoHide        disp_menuAutoHide;                  ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    int16               disp_shiftInMemory;                 ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � ������
                                                            ///< �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    Channel             disp_lastAffectedChannel;           ///< \brief ��������� ����������� �����. ������������ ��� ����������� ������ ��������
                                                            ///< �� ����� � ���������� ���� ������ �������

    // ���� ����� 1, ����� 2

    uint16              chan_shift[NumChannels];            ///< ����� ������ �� ���������
    Range               chan_range[NumChannels];            ///< ������� ������ �� ���������
    ModeCouple          chan_couple[NumChannels];           ///< ����� �� �����
    bool                chan_enable[NumChannels];           ///< �������/�������� �����
    int8                chan_balanceShiftADC[2];            ///< ���������� �������� ��� ������������ ���.
    Bandwidth           chan_Bandwidth[2];                  ///< ����������� ������.
    Resistance          chan_Resistance[2];                 ///< ������������� �����.
    bool                chan_Inverse[2];
    Divider             chan_Divider[2];                    ///< ���������.
    CalibrationMode     chan_CalibrationMode[2];            ///< ����� ����������.

    // ���� �������������

    TrigSource          trig_source;
    TrigInput           trig_input;
    TrigPolarity        trig_polarity;
    uint16              trig_lev[NumChannels];
    ModeTrig            trig_mode;
    StartMode           trig_StartMode;                     ///< ����� �������.
    TrigModeFind        trig_ModeFind;                      ///< ����� ������������� - ������� ��� �������������.

    // ���� ���¨����

    uint16              time_shift;
    TBase               time_base;
    PeakDetMode         time_PeakDet;
    TPos                time_TPos;
    SampleType          time_SampleType;
    FunctionTime        time_TimeDivXPos;
    LinkingTShift       time_LinkingTShift;                 ///< ��� �������� �������� �� �����������
    SampleType          time_SampleTypeOld;

    // ���� �������

    bool                curs_ShowCursors;                   ///< ���������� �� �������.
    CursLookMode        curs_LookMode[2];                   ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                curs_ShowFreq;                      ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    CursActive          curs_Active;                        ///< ����� ������� ����� �������.
    Channel             curs_Source;                        ///< �������� - � ������ ������ ��������� �������.
    CursCntrl           curs_CntrlU[NumChannels];           ///< �������� ������� ����������.
    CursCntrl           curs_CntrlT[NumChannels];           ///< �������� ������� �������.
    CursMovement        curs_Movement;                      ///< ��� ������������ �������� - �� ������ ��� ���������.
    float               curs_DeltaU100percents[2];          ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float               curs_DeltaT100percents[2];          ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    float               curs_PosCurU[NumChannels][2];       ///< ������� ������� �������� ���������� ����� �������.
    float               curs_PosCurT[NumChannels][2];       ///< ������� ������� �������� ������� ����� �������.

    // ���� ���������

#define MAX_SYMBOLS_IN_FILE_NAME 35
    ENumPointsFPGA      mem__enumPoints;                            ///< ����� �����
    ModeBtnMemory       mem__modeBtnMemory;
    ModeWork            mem__modeWork;                              ///< ����� ������.
    bool                mem__flashAutoConnect;                      ///< ���� true, ��� ����������� ������ ������������� ��������� ����-��������.
    int8                mem_IndexCurSymbolNameMask;                 ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    ModeSaveSignal      mem_ModeSaveSignal;                         ///< � ����� ���� ��������� ������.
    char                mem_FileName[MAX_SYMBOLS_IN_FILE_NAME];     ///< ��� ����� ��� ������ ������� �������.
    ModeShowIntMem      mem_ModeShowIntMem;                         ///< ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
    FileNamingMode      mem_FileNamingMode;                         ///< ����� ���������� ������.
    char                mem_FileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief ����� ����� ��� ��������������� ���������� ������.
                        ///< \details ������� ����������.\n
                        /// \code
                        /// %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������
                        /// %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007
                        /// �������
                        /// name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32
                        /// ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� 
                        /// ����� ������ ����� 0001, �.�. ��� ����������� ������ ���������������.
                        /// \endcode

    bool                meas_Show;                      ///< ���������� �� ���������.
    MeasuresNumber      meas_Number;                    ///< ������� ��������� ��������.
    MeasSource          meas_Source;                    ///< ��� ����� ������� �������� ���������.
    ModeViewSignals     meas_ModeViewSignals;           ///< ������� �� ������� ��� ������ ���������.
    Meas                meas_Measures[15];              ///< ��������� ��� ��������� ���������.
    Meas                meas_Marked;                    ///< ���������, �� ������� ����� �������� �������.

    // ���� ������

    Language            serv_lang;
    ColorScheme         serv_ColorScheme;
    bool                serv_Recorder;                  ///< ������� �� ����� ������������.
    CalibratorMode      serv_CalibratorMode;            ///< ����� ������ �����������.
    bool                serv_SoundEnable;               ///< �������� �� �����.
    int16               serv_SoundVolume;               ///< ��������� ����� [0...100].

    // ��������� ����������

    FuncModeDraw        math_modeDraw;                  ///< ���������� ��� ����� ������� � ������ �������������� �������.
    bool                math_EnableFFT;
    ScaleFFT            math_ScaleFFT;
    SourceFFT           math_SourceFFT;
    WindowFFT           math_WindowFFT;
    uint8               math_CurrentCursor;             ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8               math_PosCur[2];                 ///< ������� ������� �������. ���������� 0...256.
    FFTmaxDB            math_FFTmaxDB;
    Function            math_Function;
    ModeRegSet          math_ModeRegSet;                ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Range               math_Range;
    Divider             math_Divider;
    uint16              math_RShift;

    // ��������� �����������

    bool                freq_Enable;
    TimeCounting        freq_TimeCounting;              ///< ����� ����� �������.
    FreqClc             freq_FreqClc;                   ///< ������� ����������.
    NumberPeriods       freq_NumberPeriods;             ///< ���������� ��������.

    // ���� �������

    int16               dbg__numStrings;                ///< ����� ����� � �������.
    int8                dbg__sizeFont;                  ///< ������ ������ ������� - 0 - 5, 1 - 8.
    bool                dbg__modePauseConsole;          ///< ���� true, �� ����� � ������� ��������������� �������� ������ ����/����.
    bool                dbg__showAll;
    bool                dbg__showFlag;
    bool                dbg__showRShift[2];
    bool                dbg__showTrigLev;
    bool                dbg__showRange[2];
    bool                dbg__showChanParam[2];
    bool                dbg__showTrigParam;
    bool                dbg__showTShift;
    bool                dbg__showTBase;
    int16               dbg_NumMeasuresForGates;        ///< ����� ��������� ��� �����.
    bool                dbg_ShowRandInfo;               ///< �������� ���������� �� ������������� - ������ � ��������� ��������.
    bool                dbg_ShowRandStat;               ///< �������� ������ ����������.
    int16               dbg_TimeCompensation;           ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    int16               dbg_Pretriggered;               ///< ������������ �������� ����������� ��� ������������ �������������.
    Bandwidth           dbg_Bandwidth[2];               ///< \brief ����� ������� ������, ������� ����� ���������� ��� ������ � "�����-������" 
                                                        ///< �������� "������".
    bool                dbg_ShowStats;                  ///< ���������� ���������� �� ������ (fps, ��������).
    DisplayOrientation  dbg_Orientation;

    // ��������� ������-����������

    TesterControl       test_control;
    TesterPolarity      test_polarity;
    TesterStepU         test_stepU;
    TesterStepI         test_stepI;
    uint8               test_smooth;                                ///< ���������� �����������

    // ��������� ����

    const Page*         menu_currentPage;                           ///< ��������� �� �������� �������� ����
    bool                menu_show;                                  ///< ���� true, �� ����� ���������� ������� ��������
    int8                menu_posActItem[Page_NumPages];             ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� 
                                                                    ///< ��������� ������.
    int8                menu_currentSubPage[Page_NumPages];         ///< ����� ������� �����������.

    // �������������� ��������� ����������

    int16               nrst_balanceADC[NumChannels];               ///< �������� ��������������� �������� ��� ��� ������ ������������.
    BalanceADCtype      nrst_balanceADCtype;                        ///< ��� ������������.
    StretchADCtype      nrst_stretchADCtype;                        ///< ��� �������� ������.
    int16               nrst_StretchADC[NumChannels][3];            ///< \brief ����������� ����������� ��� �������, �������������� �
                        ///< ������������ �������. ����� �������� � ����� ����, ����� �������� �������� �����������, ����� ��������� �� 1000 �
                        ///< ��������� �������.
    int16               nrst_RShiftAddStable[NumChannels][3];       ///< ���������� �������� ��� ��� ����� �������������� ����������. ������� �������� ��� ���������
    int16               nrst_NumAveForRand;                         ///< �� �������� ���������� ��������� ������ � ������ �������������.
    int16               nrst_NumSmoothForRand;                      ///< ����� ����� ��� ����������� ������ � �������������.
    int16               nrst_RShiftAdd[NumChannels][Range::Size][2];///< ���������� ��������, ������� ������� ���� ��� ���������� � ������������
    int16               nrst_CorrectionTime;                        ///< ����������� ��������� �������.
};

#pragma pack(pop)

extern Settings set;
