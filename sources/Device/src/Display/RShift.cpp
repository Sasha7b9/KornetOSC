#include "RShift.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Display/Grid.h"
#include "FPGA/FPGA.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RShift::Draw()
{
    DrawRShift(Chan::A);
    DrawRShift(Chan::B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void RShift::DrawRShift(Chan ch)
{
    Painter::SetColor(Color::Channel(ch));

    int delta = (SET_RSHIFT(ch) - RShift::ZERO) / STEP_RSHIFT;

    int y = (Grid::Bottom() - Grid::Top()) / 2 + Grid::Top() - delta;

    Painter::DrawChar(Grid::Left() - 8, y - 4, (char)SYMBOL_RSHIFT_MARKER);

    Painter::SetFont(TypeFont_5);

    Painter::DrawChar(Grid::Left() - 7, y - 6, ch.IsA() ? '1' : '2', Color::BACK);

    Painter::SetFont(TypeFont_8);
}
