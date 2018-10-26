#include "defines.h"
#include "Device.h"
#include "Display/Display.h"
#include "FPGA/FPGA.h"
#include "Menu/Menu.h"
#include "Hardware/Timer.h"
#include "Keyboard/Decoder.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include "Hardware/Sound.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include <stdlib.h>
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Device::Mode Device::currentMode = Device::Mode::Osci;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Device::Init()
{       
    Hardware::Init();

    Tester::Init();

    Display::Init();

    PAUSE_ON_MS(500);

    FPGA::Init();

    Settings::Load();

    FrequencyCounter::Init();

    FPGA::LoadSettings();

    Menu::Init();

    FPGA::OnPressStart();

    Multimeter::Init();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Device::Update()
{
    START_MULTI_MEASUREMENT();

    Display::Update();

    FPGA::Update();

    Menu::SaveSettings();

    Tester::Update();

    Multimeter::Update();

    Menu::Update();

    Decoder::Update();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Device::Mode Device::CurrentMode()
{
    return currentMode;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Device::SetMode(Mode mode)
{
    currentMode = mode;
    if(currentMode == Mode::Tester)
    {
        Tester::Enable();
    }
    else
    {
        Tester::Disable();
    }

    Menu::ChangeMode();
}
