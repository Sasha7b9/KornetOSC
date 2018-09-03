#pragma once
#include "defines.h"
#include "Utils/Measures.h"
#include "Menu/MenuItems.h"
#include "SettingsChannel.h"
#include "SettingsTime.h"
#include "SettingsMath.h"
#include "SettingsMemory.h"
#include "SettingsDebug.h"
#include "SettingsNRST.h"
#include "SettingsService.h"
#include "SettingsMeasures.h"
#include "Tester/Tester.h"
#include "Display/Cursors.h"
#include "FPGA/FPGA.h"
#include "Menu/Menu.h"
#include "Display/Grid.h"
#include "Display/Colors.h"
#include "Multimeter/Multimeter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SET_SIZE                        (set.size)
#define SET_CRC32                       (set.crc32)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IN_RANDOMIZE_MODE               (SET_TBASE < TBase::_100ns)
#define CURRENT_PAGE                    (set.menu_currentPage)

#define TRIG_MODE                       (set.trig_mode)

#define TESTER_STEP_U                   (set.test_stepU)
#define TESTER_STEP_I                   (set.test_stepI)
#define TESTER_NUM_SMOOTH               (set.test_smooth)

#define MENU_IS_SHOWN                   (set.menu_show)


/// ���������� ������� ��������� ������ �� �������� Page::Name.
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
    /// ���������� ��������� �� ��������� �� ���������
    static Settings &GetDefault();

    uint                size;                               ///< ������ ������ ��������� � ������
    uint                crc32;                              ///< \brief ����������� ����� ������ ��������� � ����������� � ��� �����������

    // ���� �������
                                                            ///< ����������� �� ������� �����, ���������� �� ���� �����
    Display::ModeDrawSignal     disp_modeDrawSignal;
    Display::ThicknessSignal    disp_thickness;                     ///< ������� �����, ������� �������� ������
    Display::Background         disp_background;                    ///< ���� ����.
    Display::ShowStrNavi        disp_showStringNavigation;          ///< ����� ������ ������ ��������� ����.
    Display::ENumMinMax         disp_ENumMinMax;                    ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    Display::ModeAveraging      disp_modeAveraging;                 ///< ��� ���������� �� ����������.
    Display::ENumAverage        disp_ENumAverage;                   ///< ����� ���������� �������.
    Display::ENumAccum          disp_ENumAccum;                     ///< ����� ���������� ������� �� ������.
    Display::ModeAccumulation   disp_modeAccumulation;              ///< ����� ���������� ��������.
    Display::ENumSmoothing      disp_ENumSmoothing;                 ///< ������������ ���������� ����� ��� ����������� �������.
    Display::ENumSignalsInSec   disp_ENumSignalsInSec;              ///< ������������ ����� ���������� ������� � �������.
    Grid::Type                  disp_typeGrid;                      ///< ��� �����
    int16               disp_brightnessGrid;                ///< ������� ����� �� 0 �� 100.
    Display::LinkingRShift      disp_linkingRShift;                 ///< ��� �������� � �������� �� ���������.
    int16               disp_brightness;                    ///< ������� �������.
    int16               disp_timeShowLevels;                ///< �����, � ������� �������� ����� ���������� ������ ��������.
    int16               disp_timeMessages;                  ///< ����� � ��������, �� ������� ��������� ������� �� �����.
    Display::AltMarkers disp_altMarkers;                    ///< ����� ����������� �������������� ������� �������� ��������.
    Menu::AutoHide      disp_menuAutoHide;                  ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    int16               disp_shiftInMemory;                 ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � 
                                                            ///< ������. �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    Chan                disp_lastAffectedChannel;           ///< \brief ��������� ����������� �����. ������������ ��� ����������� ������ ��������
                                                            ///< �� ����� � ���������� ���� ������ �������

    // ���� ����� 1, ����� 2

    uint16              chan_shift[Chan::Num];              ///< ����� ������ �� ���������
    Range               chan_range[Chan::Num];              ///< ������� ������ �� ���������
    ModeCouple          chan_couple[Chan::Num];             ///< ����� �� �����
    bool                chan_enable[Chan::Num];             ///< �������/�������� �����
    int8                chan_balanceShiftADC[2];            ///< ���������� �������� ��� ������������ ���.
    Bandwidth           chan_bandwidth[2];                  ///< ����������� ������.
    Resistance          chan_resistance[2];                 ///< ������������� �����.
    bool                chan_inverse[2];
    Divider             chan_divider[2];                    ///< ���������.
    CalibrationMode     chan_calibrationMode[2];            ///< ����� ����������.

    // ���� �������������

    Trig::Source        trig_source;
    Trig::Input         trig_input;
    Trig::Polarity      trig_polarity;
    uint16              trig_lev[Chan::Num];
    Trig::StartMode     trig_startMode;                     ///< ����� �������.
    Trig::ModeFind      trig_modeFind;                      ///< ����� ������������� - ������� ��� �������������.

    // ���� ���¨����

    int                 time_shift;
    TBase               time_base;
    PeakDetMode         time_peakDet;
    TPos                time_TPos;
    SampleType          time_sampleType;
    FunctionTime        time_timeDivXPos;
    LinkingTShift       time_linkingTShift;                 ///< ��� �������� �������� �� �����������
    SampleType          time_sampleTypeOld;

    // ���� �������

    bool                curs_showCursors;                   ///< ���������� �� �������.
    Cursors::LookMode   curs_lookMode[2];                   ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                curs_showFreq;                      ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    Cursors::Active     curs_active;                        ///< ����� ������� ����� �������.
    Chan                curs_source;                        ///< �������� - � ������ ������ ��������� �������.
    Cursors::Control    curs_cntrlU[Chan::Num];             ///< �������� ������� ����������.
    Cursors::Control    curs_cntrlT[Chan::Num];             ///< �������� ������� �������.
    Cursors::Movement   curs_movement;                      ///< ��� ������������ �������� - �� ������ ��� ���������.
    float               curs_deltaU100percents[2];          ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float               curs_deltaT100percents[2];          ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    float               curs_posCurU[Chan::Num][2];         ///< ������� ������� �������� ���������� ����� �������.
    float               curs_posCurT[Chan::Num][2];         ///< ������� ������� �������� ������� ����� �������.

    // ���� ������

#define MAX_SYMBOLS_IN_FILE_NAME 35
    ENumPointsFPGA      mem_enumPoints;                             ///< ����� �����
    ModeBtnMemory       mem_modeBtnMemory;
    ModeWork            mem_modeWork;                               ///< ����� ������.
    bool                mem_flashAutoConnect;                       ///< ���� true, ��� ����������� ������ ������������� ��������� ����-��������.
    int8                mem_indexCurSymbolNameMask;                 ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    ModeSaveSignal      mem_modeSaveSignal;                         ///< � ����� ���� ��������� ������.
    char                mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     ///< ��� ����� ��� ������ ������� �������.
    ModeShowIntMem      mem_modeShowIntMem;                         ///< ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
    FileNamingMode      mem_fileNamingMode;                         ///< ����� ���������� ������.
    char                mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief ����� ����� ��� ��������������� ���������� ������.
                        ///< \details ������� ����������.\n
                        /// \code
                        /// %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������
                        /// %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007
                        /// �������
                        /// name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32
                        /// ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� 
                        /// ����� ������ ����� 0001, �.�. ��� ����������� ������ ���������������.
                        /// \endcode

    // ���� ���������

    bool                meas_show;                      ///< ���������� �� ���������.
    MeasuresNumber      meas_number;                    ///< ������� ��������� ��������.
    MeasSource          meas_source;                    ///< ��� ����� ������� �������� ���������.
    ModeViewSignals     meas_modeViewSignals;           ///< ������� �� ������� ��� ������ ���������.
    Measures::Type      meas_measures[15];              ///< ��������� ��� ��������� ���������.
    Measures::Type      meas_marked;                    ///< ���������, �� ������� ����� �������� �������.

    // ���� ������

    Language            serv_lang;
    Color::Scheme       serv_colorScheme;
    bool                serv_recorder;                  ///< ������� �� ����� ������������.
    CalibratorMode      serv_calibratorMode;            ///< ����� ������ �����������.
    bool                serv_soundEnable;               ///< �������� �� �����.
    int16               serv_soundVolume;               ///< ��������� ����� [0...100].

    // ��������� ����������

    FuncModeDraw        math_modeDraw;                  ///< ���������� ��� ����� ������� � ������ �������������� �������.
    bool                math_enableFFT;
    ScaleFFT            math_scaleFFT;
    SourceFFT           math_sourceFFT;
    WindowFFT           math_windowFFT;
    uint8               math_currentCursor;             ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8               math_posCur[2];                 ///< ������� ������� �������. ���������� 0...256.
    FFTmaxDB            math_FFTmaxDB;
    Function            math_function;
    ModeRegSet          math_modeRegSet;                ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Range               math_range;
    Divider             math_divider;
    uint16              math_rShift;

    // ��������� �����������

    FPGA::FreqMeter::Enabled       freq_enabled;
    FPGA::FreqMeter::TimeCounting  freq_timeCounting;              ///< ����� ����� �������.
    FPGA::FreqMeter::FreqClc       freq_freqClc;                   ///< ������� ����������.
    FPGA::FreqMeter::NumberPeriods freq_numberPeriods;             ///< ���������� ��������.

    // ���� �������

    int16               dbg_numStrings;                 ///< ����� ����� � �������.
    int8                dbg_sizeFont;                   ///< ������ ������ ������� - 0 - 5, 1 - 8.
    bool                dbg_modePauseConsole;           ///< ���� true, �� ����� � ������� ��������������� �������� ������ ����/����.
    bool                dbg_showAll;
    bool                dbg_showFlag;
    bool                dbg_showRShift[2];
    bool                dbg_showTrigLev;
    bool                dbg_showRange[2];
    bool                dbg_showChanParam[2];
    bool                dbg_showTrigParam;
    bool                dbg_showTShift;
    bool                dbg_showTBase;
    int16               dbg_numMeasuresForGates;        ///< ����� ��������� ��� �����.
    bool                dbg_showRandInfo;               ///< �������� ���������� �� ������������� - ������ � ��������� ��������.
    bool                dbg_showRandStat;               ///< �������� ������ ����������.
    int16               dbg_timeCompensation;           ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    int16               dbg_pretriggered;               ///< ������������ �������� ����������� ��� ������������ �������������.
    Bandwidth           dbg_bandwidth[2];               ///< \brief ����� ������� ������, ������� ����� ���������� ��� ������ � "�����-������" 
                                                        ///< �������� "������".
    bool                  dbg_ShowStats;                ///< ���������� ���������� �� ������ (fps, ��������).
    Display::Orientation  dbg_Orientation;

    // ��������� ������-����������

    Tester::Control     test_control;
    Tester::Polarity    test_polarity;
    Tester::StepU       test_stepU;
    Tester::StepI       test_stepI;
    uint8               test_smooth;                                ///< ���������� �����������

    // ��������� ����

    const Page*         menu_currentPage;                           ///< ��������� �� �������� �������� ����
    bool                menu_show;                                  ///< ���� true, �� ����� ���������� ������� ��������
    int8                menu_posActItem[Page::Name::Number];        ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� 
                                                                    ///< ��������� ������.
    int8                menu_currentSubPage[Page::Name::Number];         ///< ����� ������� �����������.

    // �������������� ��������� ����������

    int16               nrst_balanceADC[Chan::Num];                 ///< �������� ��������������� �������� ��� ��� ������ ������������.
    BalanceADC          nrst_balanceADCtype;                        ///< ��� ������������.
    StretchADC          nrst_stretchADCtype;                        ///< ��� �������� ������.
    int16               nrst_StretchADC[Chan::Num][3];              ///< \brief ����������� ����������� ��� �������, �������������� �
                        ///< ������������ �������. ����� �������� � ����� ����, ����� �������� �������� �����������, ����� ��������� �� 1000 �
                        ///< ��������� �������.
    int16               nrst_rShiftAddStable[Chan::Num][3];         ///< ���������� �������� ��� ��� ����� �������������� ����������. ������� �������� ��� ���������
    int16               nrst_numAveForRand;                         ///< �� �������� ���������� ��������� ������ � ������ �������������.
    int16               nrst_numSmoothForRand;                      ///< ����� ����� ��� ����������� ������ � �������������.
    int16               nrst_rShiftAdd[Chan::Num][Range::Size][2];  ///< ���������� ��������, ������� ������� ���� ��� ���������� � ������������
    int16               nrst_correctionTime;                        ///< ����������� ��������� �������.

    // ��������� �����������
    Multimeter::AVP             multi_avp;
    Multimeter::Measures        multi_meas;
    Multimeter::RangeCV         multi_rangeCV;
    Multimeter::RangeVV         multi_rangeVV;
    Multimeter::RangeResistance multi_rangeResist;
};

#pragma pack(pop)

extern Settings set;
