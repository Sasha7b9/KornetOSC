#include "Device.h"
#include "Log.h"
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
DeviceMode Device::currentMode = Mode_Osci;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Device::Init()
{       
    Hardware::Init();

    Tester::Init();

    Display::Init();

    //FPGA::Init();

    Settings::Load();

    //FPGA::LoadSettings();

    Menu::Init();

    //FPGA::OnPressStart();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Device::Update()
{
    START_MULTI_MEASUREMENT();
    Menu::Update();
    Display::Update();
    Decoder::Update();

    Sound::Test();

    //FPGA::Update();
    //Menu::SaveSettings();
    //Tester::Update();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DeviceMode Device::CurrentMode()
{
    return currentMode;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Device::ChangeMode()
{
    MathOSC::CircleIncrease<uint8>((uint8 &)currentMode, 0, NumDeviceModes - 1);

    if (currentMode == Mode_Tester)
    {
        Tester::Enable();
    }
    else
    {
        Tester::Disable();
    }
}
