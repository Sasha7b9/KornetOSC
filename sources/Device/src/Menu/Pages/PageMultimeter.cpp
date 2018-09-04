#include "PageMultimeter.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Definition.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pMultimeterDC;
extern const PageBase pMultimeterAC;
extern const PageBase pMultimeterResistance;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncActive_RangesVoltageDC()
{
    return MULTI_MEASURE == Multimeter::Measures::VoltageDC;
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
    return MULTI_MEASURE == Multimeter::Measures::VoltageAC;
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
    return MULTI_MEASURE == Multimeter::Measures::Resistance;
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageMultimeter::pointer = &pMultimeterDC;

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageMultimeter::OnChanged_Mode(bool)
{
    if(MULTI_MEASURE == Multimeter::Measures::VoltageDC)
    {
        pointer = &pMultimeterDC ;
    }
    else if(MULTI_MEASURE == Multimeter::Measures::VoltageAC)
    {
        pointer = &pMultimeterAC;
    }
    else if(MULTI_MEASURE == Multimeter::Measures::Resistance)
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


DEF_PAGE_2( pMultimeterDC,
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageDC,
    Page::Name::Multimeter, Menu::pageMain, FuncActive, EmptyPressPage
)

DEF_PAGE_2(pMultimeterAC,
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesVoltageAC,
    Page::Name::Multimeter, Menu::pageMain, FuncActive, EmptyPressPage
)

DEF_PAGE_2(pMultimeterResistance,
    "����������", "MULTIMETER",
    "���������� �������� � ������ �����������",
    "Instrument control in multimeter mode",
    cMode,
    cRangesResistance,
    Page::Name::Multimeter, Menu::pageMain, FuncActive, EmptyPressPage
)
