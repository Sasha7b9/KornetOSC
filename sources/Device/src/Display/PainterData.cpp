#include "PainterData.h"
#include "defines.h"
#include "Grid.h"
#include "Log.h"
#include "Painter.h"
#include "FPGA/Storage.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Utils/MathOSC.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PainterData painterData;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterData::DrawData()
{
    uint8 *dataA = 0;
    uint8 *dataB = 0;

    storage.GetData(&dataA, &dataB);

    DrawChannel(A, dataA);
    DrawChannel(B, dataB);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawChannel(Channel ch, uint8 data[FPGA_MAX_NUM_POINTS])
{
    int bottom = grid.Bottom();
    int left = grid.Left();

    if (!SET_ENABLED(ch))
    {
        return;
    }
    
    float scale = (float)grid.Height() / 255.0f;

    if (VIEW_MODE_IS_LINES)
    {
        if (THICKNESS_SIGNAL_IS_3)
        {
            Painter::SetColor(Color::ChanHalf(ch));

            float valuePrev = bottom - data[0] * scale;

            for (int i = 1; i < 281; i++)
            {
                float value = bottom - data[i] * scale;

                Painter::DrawVLine(left + i - 2, valuePrev, value);
                Painter::DrawVLine(left + i, valuePrev, value);

                valuePrev = value;
            }
        }

        Painter::SetColor(Color::Chan(ch));

        int x = left;

        for (int i = 1; i < 281; i++)
        {
            float value = bottom - data[i] * scale;
            float valuePrev = bottom - data[i - 1] * scale;
            value += mathOSC.Sign(valuePrev - value);          // Это сделано чтобы не ухудшать вывод двумя точками на горизонтали в месте соприкоснове-
                                                            // ния двух вертикальных линий
            Painter::DrawVLine(x++, valuePrev, value);
        }
    }
    else
    {
        if (THICKNESS_SIGNAL_IS_3)
        {
            Painter::SetColor(Color::ChanHalf(ch));

            for (int i = 0; i < 280; i++)
            {
                float value = bottom - data[i] * scale;
                Painter::DrawHLine(value, left + i - 1, left + i + 1);
                Painter::DrawVLine(left + i, value - 1, value + 1);
            }
        }

        Painter::SetColor(Color::Chan(ch));

        for (int i = 0; i < 280; i++)
        {
            float value = bottom - data[i] * scale;
            Painter::SetPoint(left + i, (uint8)ROUND(value));
        }
    }
}
