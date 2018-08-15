#include "Settings.h"
#include "FPGA/FPGA.h"
#include "Hardware/EEPROM.h"
#include "Hardware/AT25160N.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Settings defaultSettings =
{
/* size                       */   0,
/* crc32                      */   0,

                                    // ���� �������

/* disp_modeDrawSignal;       */   ModeDrawSignal_Lines,
/* disp_thickness;            */   Thickness_1,
/* disp_background;           */   Background_Black,
/* disp_showStringNavigation; */   ShowStrNavi_Temp,
/* disp_ENumMinMax;           */   ENumMinMax_1,
/* disp_modeAveraging;        */   ModeAveraging_Accurately,
/* disp_ENumAverage;          */   ENumAverage_1,
/* disp_ENumAccum;            */   ENumAccum_1,
/* disp_modeAccumulation;     */   ModeAccumulation_NoReset,
/* disp_ENumSmoothing;        */   ENumSmooth_Disable,
/* disp_ENumSignalsInSec;     */   ENumSignalsInSec_25,
/* disp_typeGrid;             */   TypeGrid_1,
/* disp_brightnessGrid;       */   50,
/* disp_linkingRShift;        */   LinkingRShift_Position,
/* disp_brightness;           */   100,
/* disp_timeShowLevels;       */   5,
/* disp_timeMessages;         */   5,
/* disp_altMarkers;           */   AltMarkers_AutoHide,
/* disp_menuAutoHide;         */   MenuAutoHide_None,
/* disp_shiftInMemory;        */   0,
/* disp_lastAffectedChannel;  */   A

    // ���� ����� 1, ����� 2

    // ���� �������������

    // ���� ���¨����

    // ���� �������

    // ���� ���������

    // ���� ������

    // ��������� ����������

    // ��������� �����������

    // ��������� ������-����������

    // ��������� ����

    // �������������� ��������� ����������

    /*
    {RShiftZero, RShiftZero},       // chan_shift
    {Range::_500mV, Range::_500mV}, // chan_range
    {ModeCouple_DC, ModeCouple_DC}, // chan_couple
    {true, true},                   // chan_enable
    TrigSource::A,                  // trig_source
    TrigInput::Full,                // trig_input
    TrigPolarity::Rising,           // trig_polarity
    {TrigLevZero, TrigLevZero},     // trig_lev
    ModeTrig::Auto,                 // trig_mode
    RU,                             // serv_lang
    0,                              // time_shift
    TBase::_500us,                  // time_base
    Control_Voltage,                // test_control
    Polarity_Positive,              // test_polarity
    StepU_100mV,                    // test_stepU
    StepI_4mA,                      // test_stepI
    0,                              // test_smooth
    FNP_512,                        // mem__enumPoints
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
    static const char *names[Range::Size][NumLanguages] =
    {
        {"2��",     "2mV"},
        {"5��",     "5mV"},
        {"10��",    "10mV"},
        {"20��",    "20mV"},
        {"50��",    "50mV"},
        {"0.1�",    "0.1V"},
        {"0.2�",    "0.2V"},
        {"0.5�",    "0.5V"},
        {"1�",      "1V"},
        {"2�",      "2V"},
        {"5�",      "5V"},
        {"10�",     "10V"},
        {"20�",     "20V"}
    };

    return names[range][LANG];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameTBase(TBase tBase)
{
    static const char *names[TBase::Size][NumLanguages] =
    {
        {"2��",     "2ns"},
        {"5��",     "5ns"},
        {"10��",    "10ns"},
        {"20��",    "20ns"},
        {"50��",    "50ns"},
        {"0.1���",  "0.1us"},
        {"0.2���",  "0.2us"},
        {"0.5���",  "0.5us"},
        {"1���",    "1us"},
        {"2���",    "2us"},
        {"5���",    "5us"},
        {"10���",   "10us"},
        {"20���",   "20us"},
        {"50���",   "50us"},
        {"0.1��",   "0.1ms"},
        {"0.2��",   "0.2ms"},
        {"0.5��",   "0.5ms"},
        {"1��",     "1ms"},
        {"2��",     "2ms"},
        {"5��",     "5ms"},
        {"10��",    "10ms"},
        {"20��",    "20ms"},
        {"50��",    "50ms"},
        {"0.1�",    "0.1s"},
        {"0.2�",    "0.2s"},
        {"0.5�",    "0.5s"},
        {"1�",      "1s"},
        {"2�",      "2s"},
        {"5�",      "5s"},
        {"10�",     "10s"}
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
