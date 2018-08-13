#include "RShift.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Display/Grid.h"
#include "FPGA/FPGA.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RShift::Draw()
{
    DrawRShift(A);
    DrawRShift(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void RShift::DrawRShift(Channel ch)
{
    Painter::SetColor(Color::Chan(ch));

    int delta = (SET_RSHIFT(ch) - RShiftZero) / STEP_RSHIFT;

    int y = (Grid::Bottom() - Grid::Top()) / 2 + Grid::Top() - delta;

    Painter::DrawChar(Grid::Left() - 8, y - 4, (char)SYMBOL_RSHIFT_MARKER);

    Painter::SetFont(TypeFont_5);

    Painter::DrawChar(Grid::Left() - 7, y - 6, ch == A ? '1' : '2', Color::BACK);

    Painter::SetFont(TypeFont_8);
}
