#include "Settings.h"
#include "FPGA/FPGA.h"
#include "Hardware/EEPROM.h"
#include "Hardware/AT25160N.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern col_val GlobalColors[32] =
{
/* 0  */    MAKE_COLOR(0x00, 0x00, 0x00),   // BLACK
/* 1  */    MAKE_COLOR(0xff, 0xff, 0xff),   // WHITE
/* 2  */    MAKE_COLOR(25,   25,   25),     // GRAY_10
/* 3  */    MAKE_COLOR(0x40, 0x40, 0x40),   // GRAY_25
/* 4  */    MAKE_COLOR(0x80, 0x80, 0x80),   // GRAY_50
/* 5  */    MAKE_COLOR(0xc0, 0xc0, 0xc0),   // GRAY_75
/* 6  */    MAKE_COLOR(0x00, 0x00, 0xff),   // BLUE
/* 7  */    MAKE_COLOR(0x00, 0x00, 25),     // BLUE_10
/* 8  */    MAKE_COLOR(0x00, 0x00, 0x40),   // BLUE_25
/* 9  */    MAKE_COLOR(0x00, 0x00, 0x80),   // BLUE_50
/* 10 */    MAKE_COLOR(0x00, 0x00, 0xc0),   // BLUE_75
/* 11 */    MAKE_COLOR(0x00, 0xff, 0x00),   // GREEN
/* 12 */    MAKE_COLOR(0x00, 13,   0x00),   // GREEN_5
/* 13 */    MAKE_COLOR(0x00, 25,   0x00),   // GREEN_10
/* 14 */    MAKE_COLOR(0x00, 0x40, 0x00),   // GREEN_25
/* 15 */    MAKE_COLOR(0x00, 0x80, 0x00),   // GREEN_50
/* 16 */    MAKE_COLOR(0x00, 0xc0, 0x00),   // GREEN_75
/* 17 */    MAKE_COLOR(0xff, 0x00, 0x00),   // RED
/* 18 */    MAKE_COLOR(0x40, 0x00, 0x00),   // RED_25
/* 19 */    MAKE_COLOR(0x80, 0x00, 0x00),   // RED_50
/* 20 */    MAKE_COLOR(0xc0, 0x00, 0x00),   // RED_75
/* 21 */    MAKE_COLOR(0x00, 0x00, 0x80),   // CHAN_A_HALF
/* 22 */    MAKE_COLOR(0x00, 0x80, 0x00),   // CHAN_B_HALF
/* 23 */    MAKE_COLOR(0x00, 0x00, 0xff),   // CHAN_A
/* 24 */    MAKE_COLOR(0x00, 0xff, 0x00),   // CHAN_B
/* 25 */    MAKE_COLOR(0xaf, 0xaf, 0xaf)    // GRID
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Settings defaultSettings =
{
    0,                              // size
    0,                              // crc32

    Mode_Lines,                     // disp_modeDrawSignal
    Thickness_1,                    // disp_thickness

    {RShiftZero, RShiftZero},       // chan_shift
    {Range_500mV, Range_500mV},     // chan_range
    {Couple_DC, Couple_DC},         // chan_couple
    {true, true},                   // chan_enable

    A,                              // trig_source
    TrigInput_Full,                 // trig_input
    Polarity_Rising,                // trig_polarity
    TrigLevZero,                    // trig_lev
    ModeTrig_Auto,                  // trig_mode

    RU,                        // serv_lang

    0,                              // time_shift
    TBase_500us,                    // time_base

    Control_Voltage,                // test_control
    Polarity_Positive,              // test_polarity
    StepU_100mV,                    // test_stepU
    StepI_4mA,                      // test_stepI
    0,                              // test_smooth

    EnumPoints_512,                 // mem__enumPoints
        
    0,                              // menu_currentPage
    false                           // menu_show
};

Settings set;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::Load()
{
    Reset();
    EEPROM::LoadSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Save()
{
    EEPROM::SaveSettings();

    AT25160N::Save(set);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Reset()
{
    set = defaultSettings;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameRange(Range range)
{
    static const char *names[RangeSize][NumLanguages] =
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

    return names[range][LANGUAGE];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameTBase(TBase tBase)
{
    static const char *names[TBaseSize][NumLanguages] =
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

    return names[tBase][LANGUAGE];
}
