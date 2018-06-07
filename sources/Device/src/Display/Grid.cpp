#include "Grid.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Grid::Left()
{
    return LEFT;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Top()
{
    return 22;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Width()
{
    return 280;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Height()
{
    return 200;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Bottom()
{
    return Top() + Height();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::FullBottom()
{
    return Bottom();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Right()
{
    return Left() + Width();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::NumRows()
{
    return 10;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::NumCols()
{
    return 14;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::Delta()
{
    return 20;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::MathBottom()
{
    return Bottom();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Grid::MathHeight()
{
    return Height();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Grid::Draw()
{
    int x0 = Grid::Left();
    int y0 = Grid::Top();

    Painter::DrawVLine(x0 + Grid::WIDTH / 2, y0, y0 + Grid::HEIGHT, Color::GRID);

    Painter::DrawHLine(y0 + Grid::HEIGHT / 2, x0, x0 + Grid::WIDTH);

    for (int x = x0; x < x0 + Grid::Width(); x += Grid::SIZE_CELL)
    {
        Painter::DrawVLine(x, y0, y0 + Grid::HEIGHT);
    }

    for (int y = y0; y < y0 + Grid::HEIGHT; y += Grid::SIZE_CELL)
    {
        Painter::DrawHLine(y, x0, x0 + Grid::WIDTH);
    }

    Painter::DrawRectangle(x0, y0, Grid::WIDTH, Grid::HEIGHT, Color::FILL);
}
