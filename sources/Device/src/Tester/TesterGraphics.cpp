#include "Tester.h"
#include "Display/Painter.h"
#include "Display/Display.h"
#include "Menu/Menu.h"
#include "Utils/MathOSC.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tester::Graphics::Update()
{
    Painter::BeginScene(Color::BACK);

    int size = 239;

    Painter::DrawRectangle(0, 0, size, size, Color::FILL);
    Painter::DrawRectangle(0, 0, Display::WIDTH - 1, Display::HEIGHT - 1);

    for (int i = 0; i < NUM_STEPS; i++)
    {
        DrawData(i, 0, 0);
    }

    Menu::Draw();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Tester::Graphics::DrawData(int numStep, int x0, int y0)
{
    static const Color colors[5] = {Color::FILL, Color::GRID, Color::RED, Color::GREEN, Color::BLUE};

    uint8 *dataX = &Tester::data[Chan::A][numStep][0];
    uint8 *dataY = &Tester::data[Chan::B][numStep][0];

    Painter::SetColor(colors[numStep]);

    MathOSC::Smoothing(dataX, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);
    MathOSC::Smoothing(dataY, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);

    if (TESTER_VIEW_MODE_IS_LINES)
    {
        int x1 = x0 + TESTER_NUM_POINTS - (dataX[1] - MIN_VALUE);
        int y1 = y0 + dataY[1] - MIN_VALUE;
        for (int i = 2; i < TESTER_NUM_POINTS; i++)
        {
            int x2 = x0 + TESTER_NUM_POINTS - (dataX[i] - MIN_VALUE);
            int y2 = y0 + dataY[i] - MIN_VALUE;
            Painter::DrawLine(x1, y1, x2, y2);
            x1 = x2;
            y1 = y2;
        }
    }
    else
    {
        for (int i = 0; i < TESTER_NUM_POINTS; i++)
        {
            int x = x0 + TESTER_NUM_POINTS - (dataX[i] - MIN_VALUE);
            int y = y0 + dataY[i] - MIN_VALUE;

            if (x > x0 && x < x0 + TESTER_NUM_POINTS && y > y0 && y < y0 + TESTER_NUM_POINTS)
            {
                Painter::SetPoint(x, y);
            }
        }
    }
}
