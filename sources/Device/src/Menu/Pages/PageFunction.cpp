#include "defines.h"
#include "PageFunction.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Hardware/Sound.h"
#include "Definition.h"
#include "Display/Painter.h"
#include "PageMultimeter.h"
#include "PageTester.h"
#include "PageFunctionFFT.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageFunction;

extern const PageBase ppFreqMeter;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChanged_FreqMeter_Enable(bool)
{
    FrequencyCounter::Init();
}

DEF_CHOICE_2(cFreqMeter_Enable,                                                                            //--- ������� - ���������� - ���������� ---
    "����������", "Freq meter",
    "",
    "",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    (FREQ_METER_ENABLED.value), ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(cFreqMeter_TimeF,                                                                          //--- ������� - ���������� - ����� ����� F ---
    "����� ����� F", "Time calc F",
    "��������� ������� �������� ��������� ������� - ��� ������ �����, ��� ������ �������� � ������ ����� ���������",
    "Allows to choose the accuracy of measurement of frequency - the more time, the accuracy more time of measurement is more",
    "100��", "100ms",
    "1�", "1s",
    "10�", "10ms",
    FREQ_METER_TIMECOUNTING, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_4(cFreqMeter_FreqClc,                                                                        //--- ������� - ���������� - ����� ������� ---
    "����� �������", "Timestamps",
    "����� ������� ���������� ������� ���������",
    "Choice of frequency of following of calculating impulses",
    "100���", "10MHz",
    "1���", "200MHz",
    "10���", "10MHz",
    "100���", "100MHz",
    FREQ_METER_FREQ_CLC, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(cFreqMeter_NumPeriods,                                                                   //--- ������� - ���������� - ���-�� �������� ---
    "��� ��������", "Num periods",
    "��������� ������� �������� ��������� ������� - ��� ������ �����, ��� ������ �������� � ������ ����� ���������",
    "Allows to choose the accuracy of measurement of period - the more time, the accuracy more time of measurement is more",
    "1", "1",
    "10", "10",
    "100", "100",
    FREQ_METER_NUM_PERIODS, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4(ppFreqMeter,                                                                                                 //--- ������� - ���������� ---
    "����������", "FREQ METER",
    "",
    "",
    cFreqMeter_Enable,      // ��������� - ���������� - ����������
    cFreqMeter_TimeF,       // ��������� - ���������� - ����� ����� F
    cFreqMeter_FreqClc,     // ��������� - ���������� - ����� �������
    cFreqMeter_NumPeriods,  // ��������� - ���������� - ���-�� ��������
    Page::Name::Service_FreqMeter, &pageFunction, FuncActive, EmptyPressPage
)



const PageBase *PageFunction::pointer = &pageFunction;

const PageBase *PageFrequencyCounter::pointer = &ppFreqMeter;

const Choice *PageFrequencyCounter::GetChoiceTimeF()
{
    return (const Choice *)&cFreqMeter_TimeF;
}

const Choice *PageFrequencyCounter::GetChoiceFreqClc()
{
    return (const Choice *)&cFreqMeter_FreqClc;
}

const Choice *PageFrequencyCounter::GetChoiceNumPeriods()
{
    return (const Choice *)&cFreqMeter_NumPeriods;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageFunction,                                                                                                            //--- ������� ---
    "�������", "FUNCTION",
    "����� �������",
    "Function selection",
    ppFreqMeter,                // ������� - ����������
    *PageFunctionFFT::pointer,  // ������� - ������
    *PageMultimeter::pointer,   // ������� - ����������
    *PageTester::pointer,       // ������� - ������
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)
