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
    static int MathTop();

    /// Ќарисовать сетку
    static void Draw();

private:

    static void DrawGridSignal(int left, int top, int width, int height);

    static void DrawGridSpectrum();

    static float DeltaY();

    static float DeltaX();

    static void DrawGridType1(int left, int top, int right, int bottom, float centerX, float centerY, float deltaX, float deltaY, float stepX, float stepY);

    static void DrawGridType2(int left, int top, int right, int bottom, int deltaX, int deltaY, int stepX, int stepY);

    static void DrawGridType3(int left, int top, int right, int bottom, int centerX, int centerY, int deltaX, int deltaY, int stepX);

    static int  DeltaVforLineGrid();
    /// ¬озвращает рассто€ние между 
    static int  DeltaHforLineGrid();
};
