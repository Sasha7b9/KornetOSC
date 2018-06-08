#include "BottomPart.h"
#include "Settings/Settings.h"
#include "Grid.h"
#include "Painter.h"
#include "Utils/MathOSC.h"
#include "FPGA/FPGAMath.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BottomPart::Draw()
{
    int x = WriteChannel(A, Grid::LEFT, Grid::Bottom() + 1);
    WriteChannel(B, Grid::LEFT, Grid::Bottom() + 9);
    WriteTBase(x, Grid::Bottom() + 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int BottomPart::WriteChannel(Channel ch, int x, int y)
{
    Painter::DrawText(x, y, ch == A ? "1:" : "2:", Color::Chan(ch));

    x += 7;

    static const char symbols[3] = {SYMBOL_COUPLE_AC, SYMBOL_COUPLE_DC, SYMBOL_COUPLE_GND};

    char string[2] = {symbols[SET_COUPLE(ch)], 0};

    Painter::DrawText(x, y, string);

    x += 8;

    Painter::DrawText(x, y, NameRange(SET_RANGE(ch)));

    x += 22;

    CHAR_BUF(buf, 20);

    MathOSC::Voltage2String(RSHIFT_2_ABS(SET_RSHIFT(ch), SET_RANGE(ch)), true, buf);

    Painter::DrawText(x, y, buf);

    return x + 47;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BottomPart::WriteTBase(int x, int y)
{
    Painter::DrawText(x, y, NameTBase(SET_TBASE), Color::FILL);
}
