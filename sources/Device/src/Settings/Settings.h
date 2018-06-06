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
#define ETH_ENABLED             (set.eth_enable)
#define ETH_PORT                (set.eth_port)

#define IN_RANDOMIZE_MODE               (SET_TBASE < TBase_100ns)
#define CURRENT_PAGE                    (set.menu_currentPage)

#define VIEW_MODE                       (set.disp_modeDrawSignal)
#define VIEW_MODE_IS_LINES              (VIEW_MODE == Mode_Lines)
#define THICKNESS_SIGNAL                (set.disp_thickness)
#define THICKNESS_SIGNAL_IS_3           (THICKNESS_SIGNAL == Thickness_3)

#define TRIG_MODE                       (set.trig_mode)
#define TRIG_SOURCE                     (set.trig_source)

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


#define COLOR(x) GlobalColors[x]

extern uint GlobalColors[32];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings
{
public:
    static void Load(bool _default = false);
    static void Save();
    static void Reset();
    /// �������� ����� �� �������� �� ���������
    static void ResetColors();

    uint            size;                       ///< ������ ������ ��������� � ������
    uint            crc32;                      ///< \brief ����������� ����� ������ ��������� � ����������� � ��� �����������. ����������� ����� 
                                                ///< ����������� �� ������� �����, ���������� �� ���� �����
    ModeDrawSignal  disp_modeDrawSignal;
    ThicknessSignal disp_thickness;             ///< ������� �����, ������� �������� ������
    uint16          chan_shift[NumChannels];    ///< ����� ������ �� ���������
    Range           chan_range[NumChannels];    ///< ������� ������ �� ���������
    ModeCouple      chan_couple[NumChannels];   ///< ����� �� �����
    bool            chan_enable[NumChannels];   ///< �������/�������� �����
    TrigSource      trig_source;
    TrigInput       trig_input;
    TrigPolarity    trig_polarity;
    uint16          trig_lev[NumChannels];
    ModeTrig        trig_mode;
    Language        serv_lang;
    uint16          time_shift;
    TBase           time_base;
    TesterControl   test_control;
    TesterPolarity  test_polarity;
    TesterStepU     test_stepU;
    TesterStepI     test_stepI;
    uint8           test_smooth;                        ///< ���������� �����������
    ENumPointsFPGA  mem__enumPoints;                    ///< ����� �����
    const Page     *menu_currentPage;                   ///< ��������� �� �������� �������� ����
    bool            menu_show;                          ///< ���� true, �� ����� ���������� ������� ��������
    int8            menu_posActItem[Page_NumPages];     ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� 
                                                        ///< ��������� ������.
    int8            menu_currentSubPage[Page_NumPages]; ///< ����� ������� �����������.
    Background      disp_background;                    ///< ���� ����.
    ModeBtnMemory   mem__modeBtnMemory;
    ModeWork        mem__modeWork;                      ///< ����� ������.
    ShowStrNavi     disp_showStringNavigation;          ///< ����� ������ ������ ��������� ����.
    bool            mem__flashAutoConnect;              ///< ���� true, ��� ����������� ������ ������������� ��������� ����-��������.
    FuncModeDraw    math_modeDraw;                      ///< ���������� ��� ����� ������� � ������ �������������� �������.
    int16           dbg__numStrings;                    ///< ����� ����� � �������.
    int8            dbg__sizeFont;                      ///< ������ ������ ������� - 0 - 5, 1 - 8.
    bool            dbg__modePauseConsole;              ///< ���� true, �� ����� � ������� ��������������� �������� ������ ����/����.
    bool            dbg__showAll;
    bool            dbg__showFlag;
    bool            dbg__showRShift[2];
    bool            dbg__showTrigLev;
    bool            dbg__showRange[2];
    bool            dbg__showChanParam[2];
    bool            dbg__showTrigParam;
    bool            dbg__showTShift;
    bool            dbg__showTBase;
    int8            chan_balanceShiftADC[2];                ///< ���������� �������� ��� ������������ ���.
    int16           nrst_balanceADC[NumChannels];           ///< �������� ��������������� �������� ��� ��� ������ ������������.
    BalanceADCtype  nrst_balanceADCtype;                    ///< ��� ������������.
    StretchADCtype  nrst_stretchADCtype;                    ///< ��� �������� ������.
    int16           nrst_StretchADC[NumChannels][3];        ///< \brief ����������� ����������� ��� �������, �������������� �
                    ///< ������������ �������. ����� �������� � ����� ����, ����� �������� �������� �����������, ����� ��������� �� 1000 �
                    ///< ��������� �������.
    int16           nrst_RShiftAddStable[NumChannels][3];   ///< ���������� �������� ��� ��� ����� �������������� ����������. ������� �������� ��� ���������
    int16           nrst_NumAveForRand;                     ///< �� �������� ���������� ��������� ������ � ������ �������������.
    int16           nrst_NumSmoothForRand;                  ///< ����� ����� ��� ����������� ������ � �������������.
    int16           dbg_NumMeasuresForGates;                ///< ����� ��������� ��� �����.
    bool            dbg_ShowRandInfo;                       ///< �������� ���������� �� ������������� - ������ � ��������� ��������.
    bool            dbg_ShowRandStat;                       ///< �������� ������ ����������.
    int16               dbg_TimeCompensation;       ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    int16               dbg_Pretriggered;           ///< ������������ �������� ����������� ��� ������������ �������������.
    Bandwidth           dbg_Bandwidth[2];           ///< \brief ����� ������� ������, ������� ����� ���������� ��� ������ � "�����-������" 
                                                ///< �������� "������".
    bool                dbg_ShowStats;              ///< ���������� ���������� �� ������ (fps, ��������).
    DisplayOrientation  dbg_Orientation;
    int16               nrst_RShiftAdd[NumChannels][RangeSize][2];  ///< ���������� ��������, ������� ������� ���� ��� ���������� � ������������
    int16               nrst_CorrectionTime;                        ///< ����������� ��������� �������.
    Bandwidth       chan_Bandwidth[2];              ///< ����������� ������.
    Resistance      chan_Resistance[2];             ///< ������������� �����.
    bool            chan_Inverse[2];
    bool            freq_Enable;
    TimeCounting    freq_TimeCounting;          ///< ����� ����� �������.
    FreqClc         freq_FreqClc;               ///< ������� ����������.
    NumberPeriods   freq_NumberPeriods;         ///< ���������� ��������.
    bool            meas_Show;                  ///< ���������� �� ���������.
    Divider         chan_Divider[2];                ///< ���������.
    ENumMinMax          disp_ENumMinMax;            ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    ColorScheme         serv_ColorScheme;
    ModeDrawSignal      disp_ModeDrawSignal;        ///< ����� ��������� �������.
    PeakDetMode    time_PeakDet;
    bool                serv_Recorder;          ///< ������� �� ����� ������������.
    ModeAveraging       disp_ModeAveraging;         ///< ��� ���������� �� ����������.
    ENumAverage         disp_ENumAverage;           ///< ����� ���������� �������.
    StartMode       trig_StartMode;                 ///< ����� �������.
    bool            curs_ShowCursors;               ///< ���������� �� �������.
    CursLookMode    curs_LookMode[2];               ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool            curs_ShowFreq;                  ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    CursActive      curs_Active;                    ///< ����� ������� ����� �������.
    Channel         curs_Source;                    ///< �������� - � ������ ������ ��������� �������.
    CursCntrl       curs_CntrlU[NumChannels];       ///< �������� ������� ����������.
    CursCntrl       curs_CntrlT[NumChannels];       ///< �������� ������� �������.
    CursMovement    curs_Movement;                  ///< ��� ������������ �������� - �� ������ ��� ���������.
    float           curs_DeltaU100percents[2];      ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float           curs_DeltaT100percents[2];      ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    float           curs_PosCurU[NumChannels][2];   ///< ������� ������� �������� ���������� ����� �������.
    ENumAccum           disp_ENumAccum;             ///< ����� ���������� ������� �� ������.
    ModeAccumulation    disp_ModeAccumulation;      ///< ����� ���������� ��������.
    ENumSmoothing       disp_ENumSmoothing;         ///< ������������ ���������� ����� ��� ����������� �������.
    ENumSignalsInSec    disp_ENumSignalsInSec;      ///< ������������ ����� ���������� ������� � �������.
    TypeGrid            disp_TypeGrid;              ///< ��� �����
    int16               disp_BrightnessGrid;        ///< ������� ����� �� 0 �� 100.
    LinkingRShift       disp_LinkingRShift;         ///< ��� �������� � �������� �� ���������.
    int16               disp_Brightness;            ///< ������� �������.
    int16               disp_TimeShowLevels;        ///< �����, � ������� �������� ����� ���������� ������ ��������.
    int16               disp_TimeMessages;          ///< ����� � ��������, �� ������� ��������� ������� �� �����.
    AltMarkers          disp_AltMarkers;            ///< ����� ����������� �������������� ������� �������� ��������.
    MenuAutoHide        disp_MenuAutoHide;          ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    MeasuresNumber      meas_Number;                ///< ������� ��������� ��������.
    MeasSource          meas_Source;                ///< ��� ����� ������� �������� ���������.
    ModeViewSignals     meas_ModeViewSignals;       ///< ������� �� ������� ��� ������ ���������.
    Meas                meas_Measures[15];          ///< ��������� ��� ��������� ���������.
    TPos            time_TPos;
    int16               disp_ShiftInMemory;         ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � ������
                                                    ///< �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    SampleType      time_SampleType;
    FunctionTime    time_TimeDivXPos;
    LinkingTShift       time_LinkingTShift;                         ///< ��� �������� �������� �� �����������
    SampleType      time_SampleTypeOld;
    TrigModeFind    trig_ModeFind;                  ///< ����� ������������� - ������� ��� �������������.
    CalibratorMode      serv_CalibratorMode;    ///< ����� ������ �����������.
    CalibrationMode chan_CalibrationMode[2];        ///< ����� ����������.
    bool            math_EnableFFT;
    ScaleFFT        math_ScaleFFT;
    SourceFFT       math_SourceFFT;
    WindowFFT       math_WindowFFT;
    uint8           math_CurrentCursor;         ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8           math_PosCur[2];             ///< ������� ������� �������. ���������� 0...256.
    FFTmaxDB        math_FFTmaxDB;
    Function        math_Function;
    ModeRegSet      math_ModeRegSet;            ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Range           math_Range;
    Divider         math_Divider;
    uint16          math_RShift;
    bool        eth_enable;
    uint8       eth_ip0;
    uint8       eth_ip1;
    uint8       eth_ip2;
    uint8       eth_ip3;
    uint16      eth_port;
    uint8       eth_mask0;
    uint8       eth_mask1;
    uint8       eth_mask2;
    uint8       eth_mask3;
    uint8       eth_gw0;
    uint8       eth_gw1;
    uint8       eth_gw2;
    uint8       eth_gw3;
    uint8       eth_mac0;
    uint8       eth_mac1;
    uint8       eth_mac2;
    uint8       eth_mac3;
    uint8       eth_mac4;
    uint8       eth_mac5;
    bool                serv_SoundEnable;       ///< �������� �� �����.
    int16               serv_SoundVolume;       ///< ��������� ����� [0...100].
    FileNamingMode  mem_FileNamingMode;             ///< ����� ���������� ������.
#define MAX_SYMBOLS_IN_FILE_NAME 35
    char            mem_FileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief ����� ����� ��� ��������������� ���������� ������.
            ///< \details ������� ����������.\n
            /// \code
            /// %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������
            /// %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007
            /// �������
            /// name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32
            /// ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� 
            /// ����� ������ ����� 0001, �.�. ��� ����������� ������ ���������������.
            /// \endcode
    int8            mem_IndexCurSymbolNameMask; ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    ModeSaveSignal  mem_ModeSaveSignal;         ///< � ����� ���� ��������� ������.
    char            mem_FileName[MAX_SYMBOLS_IN_FILE_NAME]; ///< ��� ����� ��� ������ ������� �������.
    ModeShowIntMem  mem_ModeShowIntMem;         ///< ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
    float           curs_PosCurT[NumChannels][2];   ///< ������� ������� �������� ������� ����� �������.
    Meas            meas_Marked;                ///< ���������, �� ������� ����� �������� �������.
};

#pragma pack(pop)

extern Settings set;

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
// 192.168.1.92
#define IP_ADDR0   set.eth_ip0
#define IP_ADDR1   set.eth_ip1
#define IP_ADDR2   set.eth_ip2
#define IP_ADDR3   set.eth_ip3

/*NETMASK*/
#define NETMASK_ADDR0   set.eth_mask0
#define NETMASK_ADDR1   set.eth_mask1
#define NETMASK_ADDR2   set.eth_mask2
#define NETMASK_ADDR3   set.eth_mask3

/*Gateway Address*/
#define GW_ADDR0   set.eth_gw0
#define GW_ADDR1   set.eth_gw1
#define GW_ADDR2   set.eth_gw2
#define GW_ADDR3   set.eth_gw3

#define MII_MODE

/* Uncomment the define below to clock the PHY from external 25MHz crystal (only for MII mode) */
#ifdef 	MII_MODE
#define PHY_CLOCK_MCO
#endif
