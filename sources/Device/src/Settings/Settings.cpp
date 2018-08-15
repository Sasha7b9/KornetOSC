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
    Background::Black,          /* disp_background;           */
    ShowStrNavi::Temp,          /* disp_showStringNavigation; */
    ENumMinMax::_1,             /* disp_ENumMinMax;           */
    ModeAveraging::Accurately,  /* disp_modeAveraging;        */
    ENumAverage::_1,            /* disp_ENumAverage;          */
    ENumAccum::_1,              /* disp_ENumAccum;            */
    ModeAccumulation::NoReset,  /* disp_modeAccumulation;     */
    ENumSmoothing::Disable,     /* disp_ENumSmoothing;        */
    ENumSignalsInSec::_25,      /* disp_ENumSignalsInSec;     */
    TypeGrid::_1,               /* disp_typeGrid;             */
    50,                         /* disp_brightnessGrid;       */
    LinkingRShift::Position,    /* disp_linkingRShift;        */
    100,                        /* disp_brightness;           */
    5,                          /* disp_timeShowLevels;       */
    5,                          /* disp_timeMessages;         */
    AltMarkers::AutoHide,       /* disp_altMarkers;           */
    MenuAutoHide::None,         /* disp_menuAutoHide;         */
    0,                          /* disp_shiftInMemory;        */
    A,                          /* disp_lastAffectedChannel;  */

        // Меню КАНАЛ 1, КАНАЛ 2

    { RShiftZero, RShiftZero },                             /* chan_shift[NumChannels];  */
    { Range::_500mV, Range::_500mV },                       /* chan_range[NumChannels];  */
    { ModeCouple::DC, ModeCouple::DC },                     /* chan_couple[NumChannels]; */
    { true, true },                                         /* chan_enable[NumChannels]; */
    { 0, 0 },                                               /* chan_balanceShiftADC[2];  */
    { Bandwidth::_20MHz, Bandwidth::_20MHz },               /* chan_bandwidth[2];        */
    { Resistance::_1Mom, Resistance::_1Mom },               /* chan_resistance[2];       */
    { false, false },                                       /* chan_inverse[2];          */
    { Divider::_1, Divider::_1 },                           /* chan_divider[2];          */
    { CalibrationMode::Disable, CalibrationMode::Disable },   /* chan_calibrationMode[2];  */

        // Меню СИНХРОНИЗАЦИЯ

    TrigSource::A,                  /* trig_source;              */
    TrigInput::Full,                /* trig_input;               */
    TrigPolarity::Rising,           /* trig_polarity;            */
    { TrigLevZero, TrigLevZero },   /* trig_lev[NumChannels];    */
    StartMode::Auto,                /* trig_startMode;           */
    TrigModeFind::Hand,             /* trig_modeFind;            */

        // Меню РАЗВЁРТКА

     0,                             /* time_shift;               */
     TBase::_500us,                 /* time_base;                */
     PeakDetMode::Disabled,         /* time_peakDet;             */
     TPos::Center,                  /* time_TPos;                */
     SampleType::Real,              /* time_sampleType;          */
     FunctionTime::Time,            /* time_timeDivXPos;         */
     LinkingTShift::Time,           /* time_linkingTShift;       */
     SampleType::Real,              /* time_sampleTypeOld;       */

        // Меню КУРСОРЫ

    false,                                      /* curs_showCursors;             */
    { CursLookMode::None, CursLookMode::None }, /* curs_lookMode[2];             */
    true,                                       /* curs_showFreq;                */
    CursActive::None,                           /* curs_active;                  */
    A,                                          /* curs_source;                  */
    { CursCntrl::Disable, CursCntrl::Disable }, /* curs_cntrlU[NumChannels];     */
    { CursCntrl::Disable, CursCntrl::Disable }, /* curs_cntrlT[NumChannels];     */
    CursMovement::Pixels,                       /* curs_movement;                */
    { 100, 100 },                               /* curs_deltaU100percents[2];    */
    { 100, 100 },                               /* curs_deltaT100percents[2];    */
    { { 100, 100 },{ 100, 100 } },              /* curs_posCurU[NumChannels][2]; */
    { { 100, 100 },{ 100, 100 } },              /* curs_posCurT[NumChannels][2]; */

        // Меню ПАМЯТЬ

    ENumPointsFPGA::_512,   /* mem_enumPoints;                             */
    ModeBtnMemory::Menu,    /* mem_modeBtnMemory;                          */
    ModeWork::Dir,          /* mem_modeWork;                               */
    false,                  /* mem_flashAutoConnect;                       */
    0,                      /* mem_indexCurSymbolNameMask;                 */
    ModeSaveSignal::BMP,    /* mem_modeSaveSignal;                         */
    {},                     /* mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     */
    ModeShowIntMem::Saved,  /* mem_modeShowIntMem;                         */
    FileNamingMode::Mask,   /* mem_fileNamingMode;                         */
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
