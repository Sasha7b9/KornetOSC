#include "FPGA/FPGA.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "PageTrig.h"

 
//----------------------------------------------------------------------------------------------------------------------------------- СИНХР - Режим --
static const char *itemsMode[] = { "Авто",      "Auto",
                                   "Ждущий",    "Wait",
                                   "Однократн", "Once" };

static void OnChanged_Mode()
{
    FPGA::LoadTrigMode();
}

static const Choice cMode("Режим", "Mode", itemsMode, &TRIG_MODE, 3, OnChanged_Mode);

//-------------------------------------------------------------------------------------------------------------------------------- СИНХР - Источник --
static const char *itemsSource[] = { "Канал 1", "Channel 1",
                                     "Канал 2", "Channel 2" };

static void OnChanged_Source()
{
    FPGA::LoadTrigSource();
}

static const Choice cSource("Источник", "Source", itemsSource, &TRIG_SOURCE, 2, OnChanged_Source);

//------------------------------------------------------------------------------------------------------------------------------ СИНХР - Полярность --
static const char *itemsPolarity[] = { "Фронт", "Rising",
                                       "Срез",  "Falling" };

static void OnChanged_Polarity()
{
    FPGA::LoadTrigPolarity();
}

static const Choice cPolarity("Полярность", "Polarity", itemsPolarity, &TRIG_POLARITY, 2, OnChanged_Polarity);

//------------------------------------------------------------------------------------------------------------------------------------ СИНХР - Вход --
static const char *itemsInput[] = { "ПС", "Full",
                                    "ВЧ", "HF",
                                    "НЧ", "LF" };

static void OnChanged_Input()
{
    FPGA::LoadTrigInput();
}

static const Choice cInput("Вход", "Input", itemsInput, &TRIG_INPUT, 3, OnChanged_Input);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// СИНХР //
static const Control *controlsTrig[] = {&cMode, &cSource, &cPolarity, &cInput};

Page pageTrig("СИНХР", "TRIG", controlsTrig, 4);
