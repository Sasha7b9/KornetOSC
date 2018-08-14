#include "DisplayOsci.h"
#include "Painter.h"
#include "Grid.h"
#include "BottomPart.h"
#include "RShift.h"
#include "PainterData.h"
#include "Console.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGATypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DELTA 5


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayOsci::Update()
{
    Painter::BeginScene(Color::BACK);

    Grid::Draw();

    BottomPart::Draw();

    RShift::Draw();

    DrawCursorTrigLevel();

    PainterData::DrawData();

    DrawHiPart();

    Console::Draw();

    Menu::Draw();

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DisplayOsci::DrawCursorTrigLevel()
{
    TrigSource ch = TRIG_SOURCE;
    int trigLev = SET_TRIGLEV_SOURCE + (TRIG_SOURCE_IS_EXT ? 0 : (SET_RSHIFT((Channel)ch) - RShiftZero));
    float scale = 1.0f / ((TrigLevMax - TrigLevMin) / 2.4f / Grid::Height());
    int y0 = (Grid::Top() + Grid::Bottom()) / 2 + (int)(scale * (TrigLevZero - TrigLevMin));
    int y = y0 - (int)(scale * (trigLev - TrigLevMin));

    if (!TRIG_SOURCE_IS_EXT)
    {
        y = (y - Grid::ChannelCenterHeight()) + Grid::ChannelCenterHeight();
    }

    int x = Grid::Right();
    Painter::SetColor(Color::Trig());

    if (y > Grid::Bottom())
    {
        Painter::DrawChar(x + 3, Grid::Bottom() - 11, SYMBOL_TRIG_LEV_LOWER);
        Painter::SetPoint(x + 5, Grid::Bottom() - 2);
        y = Grid::Bottom() - 7;
        x--;
    }
    else if (y < Grid::Top())
    {
        Painter::DrawChar(x + 3, Grid::Top() + 2, SYMBOL_TRIG_LEV_ABOVE);
        Painter::SetPoint(x + 5, Grid::Top() + 2);
    }
    else
    {
        Painter::DrawChar(x + 1, y - 4, SYMBOL_TRIG_LEV_NORMAL);
    }

    Painter::SetFont(TypeFont_5);

    const char symbols[3] = {'1', '2', 'В'};
    int dY = 0;

    Painter::DrawChar(x + 5, y - 9 + dY, symbols[(uint8)TRIG_SOURCE], Color::BACK);
    Painter::SetFont(TypeFont_8);

    DrawScaleLine(Display::WIDTH - 11, true);
    int left = Grid::Right() + 9;
    int height = Grid::Height() - 2 * DELTA;
    int shiftFullMin = RShiftMin + TrigLevMin;
    int shiftFullMax = RShiftMax + TrigLevMax;
    scale = (float)height / (shiftFullMax - shiftFullMin);
    int shiftFull = SET_TRIGLEV_SOURCE + (TRIG_SOURCE_IS_EXT ? 0 : SET_RSHIFT((Channel)ch));
    int yFull = Grid::Top() + DELTA + height - (int)(scale * (shiftFull - RShiftMin - TrigLevMin) + 4);
    Painter::FillRegion(left + 2, yFull + 1, 4, 6, Color::Trig());
    Painter::SetFont(TypeFont_5);
    Painter::DrawChar(left + 3, yFull - 5 + dY, symbols[(uint8)TRIG_SOURCE], Color::BACK);
    Painter::SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DisplayOsci::DrawHiPart()
{
    WriteCursors();
    DrawHiRightPart();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DisplayOsci::DrawScaleLine(int x, bool forTrigLev)
{
    int width = 6;
    int topY = Grid::Top() + DELTA;
    int x2 = width + x + 2;
    int bottomY = Grid::Bottom() - DELTA;
    int centerY = (Grid::Bottom() + Grid::Top()) / 2;
    int levels[] =
    {
        topY,
        bottomY,
        centerY,
        centerY - (bottomY - topY) / (forTrigLev ? 8 : 4),
        centerY + (bottomY - topY) / (forTrigLev ? 8 : 4)
    };

    for (int i = 0; i < 5; i++)
    {
        Painter::DrawLine(x + 1, levels[i], x2 - 1, levels[i], Color::FILL);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DisplayOsci::WriteCursors()
{
    /*
    char buffer[20];
    int startX = 43;
    if(MODE_WORK_IS_DIR)
    {
        startX += 29;
    }
    int x = startX;
    int y1 = 0;
    int y2 = 9;
    if(sCursors_NecessaryDrawCursors())
    {
        Painter::DrawVLine(x, 1, GRID_TOP - 2, Color::FILL);
        x += 3;
        Channel source = CURS_SOURCE;
        Color colorText = Color::CHAN[source];
        if (CURsU_ENABLED)
        {
            Painter::DrawText(x, y1, "1:", colorText);
            Painter::DrawText(x, y2, "2:");
            x += 7;
            Painter::DrawText(x, y1, sCursors_GetCursVoltage(source, 0, buffer));
            Painter::DrawText(x, y2, sCursors_GetCursVoltage(source, 1, buffer));
            x = startX + 49;
            float pos0 = MathFPGA::VoltageCursor(sCursors_GetCursPosU(source, 0), SET_RANGE(source), SET_RSHIFT(source));
            float pos1 = MathFPGA::VoltageCursor(sCursors_GetCursPosU(source, 1), SET_RANGE(source), SET_RSHIFT(source));
            float delta = fabsf(pos1 - pos0);
            if(SET_DIVIDER_10(source))
            {
                delta *= 10;
            }
            Painter::DrawText(x, y1, ":dU=");
            Painter::DrawText(x + 17, y1, Voltage2String(delta, false, buffer));
            Painter::DrawText(x, y2, ":");
            Painter::DrawText(x + 10, y2, sCursors_GetCursorPercentsU(source, buffer));
        }

        x = startX + 101;
        Painter::DrawVLine(x, 1, GRID_TOP - 2, Color::FILL);
        x += 3;
        if(CURsT_ENABLED)
        {
            Painter::SetColor(colorText);
            Painter::DrawText(x, y1, "1:");
            Painter::DrawText(x, y2, "2:");
            x += 7;
            Painter::DrawText(x, y1, sCursors_GetCursorTime(source, 0, buffer));
            Painter::DrawText(x, y2, sCursors_GetCursorTime(source, 1, buffer));
            x = startX + 153;

            /// \todo Дичь.

            
            // float p0 = 0.0f;
            // memcpy(&p0, &CURsT_POS(source, 0), sizeof(float));
            // float p1 = 0.0f;
            // memcpy(&p1, &CURsT_POS(source, 1), sizeof(float));
            

            float pos0 = MathFPGA::TimeCursor(CURsT_POS(source, 0), SET_TBASE);
            float pos1 = MathFPGA::TimeCursor(CURsT_POS(source, 1), SET_TBASE);
            float delta = fabsf(pos1 - pos0);
            Painter::DrawText(x, y1, ":dT=");
            Painter::DrawText(x + 17, y1, Time2String(delta, false, buffer));
            Painter::DrawText(x, y2, ":");
            Painter::DrawText(x + 8, y2, sCursors_GetCursorPercentsT(source, buffer));

            if(CURSORS_SHOW_FREQ)
            {
                int width = 65;
                x = Grid::Right() - width;
                Painter::DrawRectangle(x, GRID_TOP, width, 12, Color::FILL);
                Painter::FillRegion(x + 1, GRID_TOP + 1, width - 2, 10, Color::BACK);
                Painter::DrawText(x + 1, GRID_TOP + 2, "1/dT=", colorText);
                Painter::DrawText(x + 25, GRID_TOP + 2, Freq2String(1.0f / delta, false, buffer));
            }
        }
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DisplayOsci::DrawHiRightPart()
{
}
