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
#include "Utils/MathOSC.h"
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
void Device::ChangeMode()
{
    MathOSC::CircleIncrease<uint8>((uint8 &)currentMode, 0, Mode::Number - 1);

    if (currentMode == Mode::Tester)
    {
        Tester::Enable();
    }
    else
    {
        Tester::Disable();
    }

    Menu::ChangeMode();
}
