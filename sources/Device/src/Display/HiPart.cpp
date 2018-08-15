#include "HiPart.h"


void HiPart::Draw()
{
    WriteCursors();
    DrawRightPart();
}

void HiPart::WriteCursors()
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

void HiPart::DrawRightPart()
{
}
