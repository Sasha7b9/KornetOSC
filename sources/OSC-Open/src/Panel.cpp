#include "Panel.h"
#include "Display/Display.h"
#include "Hardware/Keyboard.h"
#include "Hardware/FSMC.h"
#include "Utils/Decoder.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Panel::Init()
{
    Display::Init();
    Keyboard::Init();
    FSMC::Init();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Panel::Update()
{
    uint8 data = FSMC::ReadByte();
    Decoder::AddData(data);
    FSMC::WriteBuffer();
}
