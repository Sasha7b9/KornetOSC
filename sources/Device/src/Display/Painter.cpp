#include "Painter.h"
#include "Utils/Decoder.h"
#include "Hardware/FSMC.h"
#include <string.h>
#include <stdarg.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Painter::BeginScene(Color color)
{
    uint8 buffer[2] = {PAINT_BEGIN_SCENE, color.value};
    FSMC::WriteToPanel(buffer, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::EndScene()
{
    uint8 buffer[1] = {PAINT_END_SCENE};
    FSMC::WriteToPanel(buffer, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColor(Color color)
{
    if (color != Color::NUMBER)
    {
        uint8 buffer[2] = {PAINT_SET_COLOR, color.value};
        FSMC::WriteToPanel(buffer, 2);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::FillRegion(int x, int y, int width, int height, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_FILL_REGION, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)width, (uint8)(width >> 8), (uint8)height};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawText(int x, int y, const char *text, Color color)
{
    #define MAX_SIZE_BUFFER 100
    
    if(strlen(text) + 1 > MAX_SIZE_BUFFER)
    {
        return;
    }
       
    SetColor(color);
    size_t size = (size_t)(1 + 2 + 1 + 1 + strlen(text));
    uint8 buffer[MAX_SIZE_BUFFER] = {PAINT_DRAW_TEXT, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)(size - 5)};

    uint8 *pointer = &buffer[5];

    for (uint i = 0; i < strlen(text); i++)
    {
        *pointer++ = (uint8)text[i];
    }

    FSMC::WriteToPanel(buffer, (int)size);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColorValue(Color color, col_val value)
{
    uint8 buffer[6] = {PAINT_SET_PALETTE, color.value, (uint8)value, (uint8)(value >> 8), (uint8)(value >> 16), (uint8)(value >> 24)};

    FSMC::WriteToPanel(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawRectangle(int x, int y, int width, int height, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_DRAW_RECTANGLE, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)width, (uint8)(width >> 8), (uint8)height};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawFormatText(int x, int y, Color color, char *text, ...)
{
    SetColor(color);
#define SIZE_BUFFER_DRAW_FORM_TEXT 200
    CHAR_BUF(buffer, SIZE_BUFFER_DRAW_FORM_TEXT);
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    DrawText(x, y, buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawChar(int x, int y, char symbol, Color color)
{
    DrawFormatText(x, y, color, "%c", symbol);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(int y, int x0, int x1, Color color)
{
    SetColor(color);
    uint8 buffer[6] = {PAINT_DRAW_HLINE, (uint8)y, (uint8)x0, (uint8)(x0 >> 8), (uint8)x1, (uint8)(x1 >> 8)};
    FSMC::WriteToPanel(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(float y, int x0, int x1, Color color)
{
    DrawHLine((int)y, x0, x1, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, int y0, int y1, Color color)
{
    SetColor(color);
    uint8 buffer[5] = {PAINT_DRAW_VLINE, (uint8)x, (uint8)(x >> 8), (uint8)y0, (uint8)y1};
    FSMC::WriteToPanel(buffer, 5);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, float y0, float y1, Color color)
{
    DrawVLine((int)x, (int)y0, (int)y1, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_DRAW_LINE, (uint8)x0, (uint8)(x0 >> 8), (uint8)y0, (uint8)x1, (uint8)(x1 >> 8), (uint8)y1};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetPoint(int x, int y, Color color)
{
    SetColor(color);
    uint8 buffer[4] = {PAINT_SET_POINT, (uint8)x, (uint8)(x >> 8), (uint8)y};
    FSMC::WriteToPanel(buffer, 4);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawBoundedRegion(int x, int y, int width, int height, Color colorFill, Color colorBound)
{
    DrawRectangle(x, y, width, height, colorBound);
    FillRegion(x + 1, y + 1, width - 2, height - 2, colorFill);
}
