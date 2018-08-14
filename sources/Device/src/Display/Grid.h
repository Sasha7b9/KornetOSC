#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Grid
{
public:

    ///  онстанты используютс€ дл€ расчЄта размеров, которые остаютс€ одинаковыми при любых размерах и пропорци€х сетки - например, элементов меню
    static const int WIDTH = 280;
    static const int HEIGHT = 200;
    static const int SIZE_CELL = 20;
    static const int LEFT = 20;

    /// Ёти значени€ могут мен€тьс€ в зависимости от выставленного режима
    static int Left();
    static int Top();
    static int Width();
    static int Height();
    static int Bottom();
    static int Right();
    static int NumRows();
    static int NumCols();
    static int ChannelCenterHeight();
    static int Delta();
    static int FullBottom();
    static int MathBottom();
    static int MathHeight();
    static int ChannelBottom();

    /// Ќарисовать сетку
    static void Draw();

private:
};
