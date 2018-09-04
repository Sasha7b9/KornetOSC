#include "PageMultimeter.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Definition.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pMultimeter;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncActive_RangesVoltageDC()
{
    return MULTI_MEASURE == Multimeter::Measures::VoltageDC;
}

DEF_CHOICE_3(   cRangesVoltageDC,                                                                                        //--- МУЛЬТИМЕТР - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Мeasurement range",
    "2 В",   "2 V",
    "20 В",  "20 V",
    "500 В", "500 V",
    MULTI_RANGE_DC, pMultimeter, FuncActive_RangesVoltageDC, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RnagesVoltageAC()
{
    return MULTI_MEASURE == Multimeter::Measures::VoltageAC;
}

DEF_CHOICE_3(   cRangesVoltageAC,                                                                                        //--- МУЛЬТИМЕТР - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Measurement range",
    "2 В",   "2 V",
    "20 В",  "20 V",
    "400 В", "400 V",
    MULTI_RANGE_AC, pMultimeter, FuncActive_RnagesVoltageAC, FuncChangedChoice, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RangesReistance()
{
    return MULTI_MEASURE == Multimeter::Measures::Resistance;
}

DEF_CHOICE_4(   cRangesResistance,                                                                                       //--- Мультиметр - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Measurement range",
    "2 кОм", "2 kOhm",
    "20 кОм", "20 kOhm",
    "200 кОм", "200 kOhm",
    "10 МОм", "10 MOhm",
    MULTI_RANGE_RESISTANCE, pMultimeter, FuncActive_RangesReistance, FuncChangedChoice, FuncDraw
)

static void OnChanged_Mode(bool);

DEF_CHOICE_7(   cMode,
    "Режим", "Mode"
    ,
    "Выбор типа измерениия\n"
    "U= - постоянное напряжение\n"
    "U~ - переменное напряжение\n"
    "I= - постоянный ток\n"
    "I~ - переменный ток\n"
    "R - сопротивление постоянному току\n"
    "VD - тест диодов\n"
    "BELL - прозвонка"
    ,
    "Selecting the type of measurement\n"
    "U= - DC voltage\n"
    "U~ - AC voltage\n"
    "I= - DC current\n"
    "I~ - AC current\n"
    "R - DC resistance\n"
    "VD - diodes test\n"
    "BELL - bell"
    ,
    "U=",   "U=",
    "U~",   "U~",
    "I=",   "I=",
    "I~",   "I~",
    "R",    "R",
    "VD",   "VD",
    "BELL", "BELL",
    MULTI_MEASURE, pMultimeter, FuncActive, OnChanged_Mode, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Mode(bool)
{
    /*
    const Control *const itemsDC[] = { (Control *)&cMode, (Control *)&cRangesVoltageDC };
    const Control *const itemsAC[] = { (Control *)&cMode, (Control *)&cRangesVoltageAC };
    const Control *const itemsResist[] = { (Control *)&cMode, (Control *)&cRangesResistance };

    if(MULTI_MEASURE == Multimeter::Measures::VoltageDC)
    {
        pMultimeter.items = (const Control * const *)&itemsDC;
    }
    else if(MULTI_MEASURE == Multimeter::Measures::VoltageAC)
    {
        items = itemsAC;
    }
    else if(MULTI_MEASURE == Multimeter::Measures::Resistance)
    {
        items = itemsResist;
    }
    */
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageMultimeter::pointer = &pMultimeter;


DEF_PAGE_2( pMultimeter,
    "МУЛЬТИМЕТР", "MULTIMETER",
    "Управление прибором в режиме мультиметра",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageDC,
    Page::Name::Multimeter, Menu::pageMain, FuncActive, EmptyPressPage
)
