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

DEF_CHOICE_2(cFreqMeter_Enable,                                                                            //--- ФУНКЦИЯ - ЧАСТОТОМЕР - Частотомер ---
    "Частотомер", "Freq meter",
    "",
    "",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU, ENABLE_EN,
    (FREQ_METER_ENABLED.value), ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(cFreqMeter_TimeF,                                                                          //--- ФУНКЦИЯ - ЧАСТОТОМЕР - Время счёта F ---
    "Время счёта F", "Time calc F",
    "Позволяет выбрать точность измерения частоты - чем больше время, тем больше точность и больше время измерения",
    "Allows to choose the accuracy of measurement of frequency - the more time, the accuracy more time of measurement is more",
    "100мс", "100ms",
    "1с", "1s",
    "10с", "10ms",
    FREQ_METER_TIMECOUNTING, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_4(cFreqMeter_FreqClc,                                                                        //--- ФУНКЦИЯ - ЧАСТОТОМЕР - Метки времени ---
    "Метки времени", "Timestamps",
    "Выбор частоты следования счётных импульсов",
    "Choice of frequency of following of calculating impulses",
    "100кГц", "10MHz",
    "1МГц", "200MHz",
    "10МГц", "10MHz",
    "100МГц", "100MHz",
    FREQ_METER_FREQ_CLC, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(cFreqMeter_NumPeriods,                                                                   //--- ФУНКЦИЯ - ЧАСТОТОМЕР - Кол-во периодов ---
    "Кол периодов", "Num periods",
    "Позволяет выбрать точность измерения периода - чем больше время, тем больше точность и больше время измерения",
    "Allows to choose the accuracy of measurement of period - the more time, the accuracy more time of measurement is more",
    "1", "1",
    "10", "10",
    "100", "100",
    FREQ_METER_NUM_PERIODS, ppFreqMeter, FuncActive, OnChanged_FreqMeter_Enable, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4(ppFreqMeter,                                                                                                 //--- ФУНКЦИЯ - ЧАСТОТОМЕР ---
    "ЧАСТОТОМЕР", "FREQ METER",
    "",
    "",
    cFreqMeter_Enable,      // ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Частотомер
    cFreqMeter_TimeF,       // ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Время счёта F
    cFreqMeter_FreqClc,     // ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Метки времени
    cFreqMeter_NumPeriods,  // ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Кол-во периодов
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
DEF_PAGE_4( pageFunction,                                                                                                            //--- ФУНКЦИЯ ---
    "ФУНКЦИЯ", "FUNCTION",
    "Выбор функции",
    "Function selection",
    ppFreqMeter,                // ФУНКЦИЯ - ЧАСТОТОМЕР
    *PageFunctionFFT::pointer,  // ФУНКЦИЯ - СПЕКТР
    *PageMultimeter::pointer,   // ФУНКЦИЯ - МУЛЬТИМЕТР
    *PageTester::pointer,       // ФУНКЦИЯ - ТЕСТЕР
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)
