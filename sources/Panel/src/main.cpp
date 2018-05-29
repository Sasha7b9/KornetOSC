#include "defines.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Hardware/CPU.h"
#include "Utils/Decoder.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include "Hardware/Keyboard.h"
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    CPU::Init();
    Display::Init();
    
    Painter::SetColorValue(Color::BLACK, MAKE_COLOR(0, 0, 0));
    Painter::SetColorValue(Color::WHITE, MAKE_COLOR(0xff, 0xff, 0xff));
    Painter::SetColorValue(Color::GRID, MAKE_COLOR(0xff, 0x00, 0x00));
    Painter::SetColorValue(Color::MENU_FIELD, MAKE_COLOR(0x00, 0x00, 0xff));
    Painter::SetColorValue(Color::MENU_TITLE_DARK, MAKE_COLOR(0x00, 0xff, 0x00));
    Painter::LoadPalette();

    Keyboard::Init();

    FSMC::Init();

    float speedX = 1.0f;
    float speedY = 1.0f;

    float x = 0.0f;
    float y = 0.0f;

    int width = 50;

    int i = 0;

    Color color = Color::GRID;

    while(1)
    {
        Painter::BeginScene(Color::WHITE);
        Painter::SetColor(color);
        Painter::FillRegion((int)x, (int)y, width, width);
        Painter::EndScene();

        x += speedX;
        y += speedY;

        if(x + width > 320 && speedX > 0)
        {
            speedX = -speedX;
            x = 320 - width - 5.0f;
        }
        if(x < 0 && speedX < 0)
        {
            speedX = -speedX;
            x = 0;
        }
        if(y + width > 240 && speedY > 0)
        {
            speedY = -speedY;
            y = 240 - width - 5.0f;
        }
        if(y < 0 && speedY < 0)
        {
            speedY = -speedY;
            y = 0;
        }

        i++;

        if(i == 1000)
        {
            color = Color::MENU_FIELD;
        }
        else if(i == 2000)
        {
            color = Color::MENU_TITLE_DARK;
        }
        else if(i == 3000)
        {
            color = Color::GRID;
            i = 0;
        }

        /*
        uint8 data = FSMC::ReadByte();
        Decoder::AddData(data);
        FSMC::WriteBuffer();
        */
    }
}
