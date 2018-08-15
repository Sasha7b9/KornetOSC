#include "Settings.h"
#include "FPGA/FPGA.h"
#include "Hardware/EEPROM.h"
#include "Hardware/AT25160N.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Settings defaultSettings =
{
    0,                          /* size                       */
    0,                          /* crc32                      */

        // Меню ДИСПЛЕЙ

    ModeDrawSignal::Lines,      /* disp_modeDrawSignal;       */
    ThicknessSignal::_1,        /* disp_thickness;            */
    Background_Black,           /* disp_background;           */
    ShowStrNavi_Temp,           /* disp_showStringNavigation; */
    ENumMinMax_1,               /* disp_ENumMinMax;           */
    ModeAveraging_Accurately,   /* disp_modeAveraging;        */
    ENumAverage_1,              /* disp_ENumAverage;          */
    ENumAccum_1,                /* disp_ENumAccum;            */
    ModeAccumulation_NoReset,   /* disp_modeAccumulation;     */
    ENumSmooth_Disable,         /* disp_ENumSmoothing;        */
    ENumSignalsInSec_25,        /* disp_ENumSignalsInSec;     */
    TypeGrid_1,                 /* disp_typeGrid;             */
    50,                         /* disp_brightnessGrid;       */
    LinkingRShift_Position,     /* disp_linkingRShift;        */
    100,                        /* disp_brightness;           */
    5,                          /* disp_timeShowLevels;       */
    5,                          /* disp_timeMessages;         */
    AltMarkers_AutoHide,        /* disp_altMarkers;           */
    MenuAutoHide_None,          /* disp_menuAutoHide;         */
    0,                          /* disp_shiftInMemory;        */
    A,                          /* disp_lastAffectedChannel;  */

        // Меню КАНАЛ 1, КАНАЛ 2

    { RShiftZero, RShiftZero },                             /* chan_shift[NumChannels];  */
    { Range::_500mV, Range::_500mV },                       /* chan_range[NumChannels];  */
    { ModeCouple_DC, ModeCouple_DC },                       /* chan_couple[NumChannels]; */
    { true, true },                                         /* chan_enable[NumChannels]; */
    { 0, 0 },                                               /* chan_balanceShiftADC[2];  */
    { Bandwidth_20MHz, Bandwidth_20MHz },                   /* chan_bandwidth[2];        */
    { Resistance_1Mom, Resistance_1Mom },                   /* chan_resistance[2];       */
    { false, false },                                       /* chan_inverse[2];          */
    { Divider_1, Divider_1 },                               /* chan_divider[2];          */
    { CalibrationMode_Disable, CalibrationMode_Disable },   /* chan_calibrationMode[2];  */

        // Меню СИНХРОНИЗАЦИЯ

    TrigSource::A,                  /* trig_source;              */
    TrigInput::Full,                /* trig_input;               */
    TrigPolarity::Rising,           /* trig_polarity;            */
    { TrigLevZero, TrigLevZero },   /* trig_lev[NumChannels];    */
    StartMode_Auto,                 /* trig_startMode;           */
    TrigModeFind_Hand,              /* trig_modeFind;            */

        // Меню РАЗВЁРТКА

     0,                             /* time_shift;               */
     TBase::_500us,                 /* time_base;                */
     PeakDet_Disabled,              /* time_peakDet;             */
     TPos_Center,                   /* time_TPos;                */
     SampleType_Real,               /* time_sampleType;          */
     FunctionTime_Time,             /* time_timeDivXPos;         */
     LinkingTShift_Time,            /* time_linkingTShift;       */
     SampleType_Real,               /* time_sampleTypeOld;       */

        // Меню КУРСОРЫ

    false,                                      /* curs_showCursors;             */
    { CursLookMode_None, CursLookMode_None },   /* curs_lookMode[2];             */
    true,                                       /* curs_showFreq;                */
    CursActive_None,                            /* curs_active;                  */
    A,                                          /* curs_source;                  */
    { CursCntrl_Disable, CursCntrl_Disable },   /* curs_cntrlU[NumChannels];     */
    { CursCntrl_Disable, CursCntrl_Disable },   /* curs_cntrlT[NumChannels];     */
    CursMovement_Pixels,                        /* curs_movement;                */
    { 100, 100 },                               /* curs_deltaU100percents[2];    */
    { 100, 100 },                               /* curs_deltaT100percents[2];    */
    { { 100, 100 },{ 100, 100 } },              /* curs_posCurU[NumChannels][2]; */
    { { 100, 100 },{ 100, 100 } },              /* curs_posCurT[NumChannels][2]; */

        // Меню ПАМЯТЬ

    FNP_512,                /* mem_enumPoints;                             */
    ModeBtnMemory_Menu,     /* mem_modeBtnMemory;                          */
    ModeWork_Dir,           /* mem_modeWork;                               */
    false,                  /* mem_flashAutoConnect;                       */
    0,                      /* mem_indexCurSymbolNameMask;                 */
    ModeSaveSignal_BMP,     /* mem_modeSaveSignal;                         */
    {},                     /* mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     */
    ModeShowIntMem_Saved,   /* mem_modeShowIntMem;                         */
    FileNamingMode_Mask,    /* mem_fileNamingMode;                         */
    {}                      /* mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; */

    // Меню ИЗМЕРЕНИЯ

    // Меню СЕРВИС

    // Настройки математики

    // Настройки частотомера

    // Настройки тестер-компонента

    // Настройки меню

    // Несбрасываемые настройки калибровки

    /*
    RU,                             // serv_lang
    Control_Voltage,                // test_control
    Polarity_Positive,              // test_polarity
    StepU_100mV,                    // test_stepU
    StepI_4mA,                      // test_stepI
    0,                              // test_smooth
    0,                              // menu_currentPage
    false                           // menu_show
    */
};

Settings set;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::Load(bool)
{
    Reset();
    //EEPROM::LoadSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Save()
{
    //EEPROM::SaveSettings();

    //AT25160N::Save(set);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Reset()
{
    set = defaultSettings;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameRange(Range range)
{
    static const char *names[Range::Size][Language::Num] =
    {
        {"2мВ",     "2mV"},
        {"5мВ",     "5mV"},
        {"10мВ",    "10mV"},
        {"20мВ",    "20mV"},
        {"50мВ",    "50mV"},
        {"0.1В",    "0.1V"},
        {"0.2В",    "0.2V"},
        {"0.5В",    "0.5V"},
        {"1В",      "1V"},
        {"2В",      "2V"},
        {"5В",      "5V"},
        {"10В",     "10V"},
        {"20В",     "20V"}
    };

    return names[range][LANG];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameTBase(TBase tBase)
{
    static const char *names[TBase::Size][Language::Num] =
    {
        {"2нс",     "2ns"},
        {"5нс",     "5ns"},
        {"10нс",    "10ns"},
        {"20нс",    "20ns"},
        {"50нс",    "50ns"},
        {"0.1мкс",  "0.1us"},
        {"0.2мкс",  "0.2us"},
        {"0.5мкс",  "0.5us"},
        {"1мкс",    "1us"},
        {"2мкс",    "2us"},
        {"5мкс",    "5us"},
        {"10мкс",   "10us"},
        {"20мкс",   "20us"},
        {"50мкс",   "50us"},
        {"0.1мс",   "0.1ms"},
        {"0.2мс",   "0.2ms"},
        {"0.5мс",   "0.5ms"},
        {"1мс",     "1ms"},
        {"2мс",     "2ms"},
        {"5мс",     "5ms"},
        {"10мс",    "10ms"},
        {"20мс",    "20ms"},
        {"50мс",    "50ms"},
        {"0.1с",    "0.1s"},
        {"0.2с",    "0.2s"},
        {"0.5с",    "0.5s"},
        {"1с",      "1s"},
        {"2с",      "2s"},
        {"5с",      "5s"},
        {"10с",     "10s"}
    };

    return names[tBase][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float MaxDBforFFT(FFTmaxDB maxDB)
{
    static const float arrayMAX_DB_FOR_FFT[] = {-40.0f, -60.0f, -80.0f};

    return arrayMAX_DB_FOR_FFT[maxDB];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::ResetColors()
{
}
