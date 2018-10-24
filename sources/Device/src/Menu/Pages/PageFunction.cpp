#include "defines.h"
#include "PageFunction.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Hardware/Sound.h"
#include "Definition.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageFunction;
extern const PageBase ppFFT;
extern const PageBase pppFFT_Cursors;
extern const PageBase ppFreqMeter;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cFFT_View,                                                                                       //--- ������� - ������ - ����������� ---
    "�����������", "Display",
    "�������� � ��������� ����������� �������",
    "Enables or disables the display of the spectrum",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    FFT_ENABLED, ppFFT, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cFFT_Scale,                                                                                            //--- ������� - ������ - ����� ---
    "�����", "Scale",
    "����� ������� ������ ������� - �������� ��� ���������������",
    "Sets the scale of the output spectrum - linear or logarithmic",
    "��������", "Log",
    "��������", "Linear",
    SCALE_FFT, ppFFT, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(cFFT_Source,                                                                                        //--- ������� - ������ - �������� ---
    "��������", "Source",
    "����� ��������� ��� ������� �������",
    "Selecting the source for the calculation of the spectrum",
    "����� 1", "Chan 1",
    "����� 2", "Chan 2",
    "����� 1 + 2", "Chan 1 + 2",
    SOURCE_FFT, ppFFT, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_4(cFFT_Window,                                                                                            //--- ������� - ������ - ���� ---
    "����", "Window",
    "����� ���� ��� ������� �������",
    "Sets the window to calculate the spectrum",
    "�����������", "Rectangle",
    "��������", "Hamming",
    "��������", "Blackman",
    "�����", "Hann",
    WINDOW_FFT, ppFFT, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_FFT_Range()
{
    return SCALE_FFT_IS_LOG;
}

DEF_CHOICE_3(cFFT_Range,                                                                                         //--- ������� - ������ - �������� ---
    "��������", "Range",
    "����� ����� ������ ������ ���������� �� ��������� �������",
    "Here you can set the limit of monitoring the power spectrum",
    "-40��", "-40dB",
    "-60��", "-60dB",
    "-80��", "-80dB",
    MAX_DB_FFT, ppFFT, IsActive_FFT_Range, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_SMALL_BUTTON_EXIT(bFFT_Cursors_Exit,                                                                  //--- ������� - ������ - ������� - ����� ---
    pppFFT_Cursors, FuncActive, OnPressSB_Exit, DrawSB_Exit
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_FFT_Cursors_Source()
{
    MATH_CURRENT_CUR = (uint8)((MATH_CURRENT_CUR + 1) % 2);
}

static void Draw_FFT_Cursors_Source(int x, int y)
{
    Painter::DrawText(x + 7, y + 5, MATH_CURRENT_CUR_IS_0 ? "1" : "2");
}

DEF_SMALL_BUTTON(bFFT_Cursors_Source,                                                                  //--- ������� - ������ - ������� - �������� ---
    "��������", "Source",
    "����� ��������� ��� ������� �������",
    "Source choice for calculation of a range",
    pppFFT_Cursors, FuncActive, OnPress_FFT_Cursors_Source, Draw_FFT_Cursors_Source
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsActive_FFT_Cursors()
{
    return FFT_ENABLED;
}

static void OnRegSet_FFT_Cursors(int angle)
{
    FFT_POS_CURSOR(MATH_CURRENT_CUR) += (uint8)angle;
    Sound::RegulatorShiftRotate();
}

DEF_PAGE_SB(pppFFT_Cursors,                                                                                       //--- ������� - ������ - ������� ---
    "�������", "CURSORS",
    "�������� ������� ��� ��������� ���������� �������",
    "Includes cursors to measure the parameters of the spectrum",
    &bFFT_Cursors_Exit,     // ������ - ������ - ������� - �����
    &bFFT_Cursors_Source,   // ������ - ������ - ������� - ��������
    0,
    0,
    0,
    0,
    Page::Name::SB_Service_FFT_Cursors, &ppFFT, IsActive_FFT_Cursors, EmptyPressPage, FuncDrawPage, OnRegSet_FFT_Cursors
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsActive_FFT()
{
    return !FUNC_MODE_DRAW_IS_ENABLED;
}

static void OnPress_FFT()
{
    if (!IsActive_FFT())
    {
        Display::ShowWarning(Warning::ImpossibleEnableFFT);
    }
}

DEF_PAGE_6(ppFFT,                                                                                                                //--- ������ - ������
    "������", "SPECTRUM",
    "����������� ������� �������� �������",
    "Mapping the input signal spectrum",
    cFFT_View,         // ������ - ������ - �����������
    cFFT_Scale,        // ������ - ������ - �����
    cFFT_Source,       // ������ - ������ - ��������
    cFFT_Window,       // ������ - ������ - ���� 
    pppFFT_Cursors,    // ������ - ������ - �������
    cFFT_Range,        // ������ - ������ - ��������
    Page::Name::Service_FFT, &pageFunction, IsActive_FFT, OnPress_FFT
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
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
DEF_PAGE_2( pageFunction,                                                                                                            //--- ������� ---
    "�������", "FUNCTION",
    "����� �������",
    "Function selection",
    ppFreqMeter,                // ������� - ����������
    ppFFT,                      // ������� - ������
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)
