#include "defines.h"
#include "PageMultimeter.h"
#include "Settings/Settings.h"
#include "Definition.h"
#include "PageFunction.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pMultimeterDC;
extern const PageBase pMultimeterAC;
extern const PageBase pMultimeterResistance;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncActive_RangesVoltageDC()
{
    return MULTI_MEASURE == Multimeter::Measure::VoltageDC;
}

static void OnChange_VoltageDC(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_3(   cRangesVoltageDC,                                                                                        //--- МУЛЬТИМЕТР - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Мeasurement range",
    "2 В",   "2 V",
    "20 В",  "20 V",
    "500 В", "500 V",
    MULTI_RANGE_DC, pMultimeterDC, FuncActive_RangesVoltageDC, OnChange_VoltageDC, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RnagesVoltageAC()
{
    return MULTI_MEASURE == Multimeter::Measure::VoltageAC;
}

static void OnChange_VoltageAC(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_3(   cRangesVoltageAC,                                                                                        //--- МУЛЬТИМЕТР - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Measurement range",
    "2 В",   "2 V",
    "20 В",  "20 V",
    "400 В", "400 V",
    MULTI_RANGE_AC, pMultimeterAC, FuncActive_RnagesVoltageAC, OnChange_VoltageAC, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncActive_RangesReistance()
{
    return MULTI_MEASURE == Multimeter::Measure::Resistance;
}

static void OnChange_Resistance(bool active)
{
    if(active)
    {
        Multimeter::ChangeMode();
    }
}

DEF_CHOICE_4(   cRangesResistance,                                                                                       //--- Мультиметр - Предел ---
    "Предел", "Range",
    "Диапазон измерения", "Measurement range",
    "2 кОм", "2 kOhm",
    "20 кОм", "20 kOhm",
    "200 кОм", "200 kOhm",
    "10 МОм", "10 MOhm",
    MULTI_RANGE_RESISTANCE, pMultimeterResistance, FuncActive_RangesReistance, OnChange_Resistance, FuncDraw
)

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
    MULTI_MEASURE, pMultimeterDC, FuncActive, PageMultimeter::OnChanged_Mode, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_AVP(bool)
{
    Multimeter::ChangeAVP();
}

DEF_CHOICE_2 (cAVP,
    "АВП", "ASL",
    "Автовыбор предела",
    "Auto-select limit",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    MULTI_AVP, pMultimeterDC, FuncActive, OnChanged_AVP, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageMultimeter::pointer = &pMultimeterDC;

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageMultimeter::OnChanged_Mode(bool)
{
    if(MULTI_MEASURE == Multimeter::Measure::VoltageDC)
    {
        pointer = &pMultimeterDC ;
    }
    else if(MULTI_MEASURE == Multimeter::Measure::VoltageAC)
    {
        pointer = &pMultimeterAC;
    }
    else if(MULTI_MEASURE == Multimeter::Measure::Resistance)
    {
        pointer = &pMultimeterResistance;
    }

    Menu::ChangeMode();

    Multimeter::ChangeMode();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageMultimeter::Init()
{
    OnChanged_Mode(true);
}


DEF_PAGE_3( pMultimeterDC,
    "МУЛЬТИМЕТР", "MULTIMETER",
    "Управление прибором в режиме мультиметра",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageDC,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)

DEF_PAGE_3(pMultimeterAC,
    "МУЛЬТИМЕТР", "MULTIMETER",
    "Управление прибором в режиме мультиметра",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageAC,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)

DEF_PAGE_3(pMultimeterResistance,
    "МУЛЬТИМЕТР", "MULTIMETER",
    "Управление прибором в режиме мультиметра",
    "Instrument control in multimeter mode",
    cMode,
    cRangesResistance,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)
