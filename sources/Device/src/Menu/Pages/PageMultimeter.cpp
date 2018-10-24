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

DEF_CHOICE_3(   cRangesVoltageDC,                                                                                        //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "�easurement range",
    "2 �",   "2 V",
    "20 �",  "20 V",
    "500 �", "500 V",
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

DEF_CHOICE_3(   cRangesVoltageAC,                                                                                        //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "Measurement range",
    "2 �",   "2 V",
    "20 �",  "20 V",
    "400 �", "400 V",
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

DEF_CHOICE_4(   cRangesResistance,                                                                                       //--- ���������� - ������ ---
    "������", "Range",
    "�������� ���������", "Measurement range",
    "2 ���", "2 kOhm",
    "20 ���", "20 kOhm",
    "200 ���", "200 kOhm",
    "10 ���", "10 MOhm",
    MULTI_RANGE_RESISTANCE, pMultimeterResistance, FuncActive_RangesReistance, OnChange_Resistance, FuncDraw
)

DEF_CHOICE_7(   cMode,
    "�����", "Mode"
    ,
    "����� ���� ����������\n"
    "U= - ���������� ����������\n"
    "U~ - ���������� ����������\n"
    "I= - ���������� ���\n"
    "I~ - ���������� ���\n"
    "R - ������������� ����������� ����\n"
    "VD - ���� ������\n"
    "BELL - ���������"
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
    "���", "ASL",
    "��������� �������",
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
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageDC,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)

DEF_PAGE_3(pMultimeterAC,
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageAC,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)

DEF_PAGE_3(pMultimeterResistance,
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesResistance,
    cAVP,
    Page::Name::Multimeter, PageFunction::pointer, FuncActive, EmptyPressPage
)
