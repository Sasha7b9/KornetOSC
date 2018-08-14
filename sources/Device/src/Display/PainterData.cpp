#include "PainterData.h"
#include "defines.h"
#include "Colors.h"
#include "Grid.h"
#include "Log.h"
#include "Painter.h"
#include "Data/Storage.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Utils/MathOSC.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterData::DrawData()
{
    uint8 *dataA = 0;
    uint8 *dataB = 0;

    Storage::GetData(&dataA, &dataB);

    DrawChannel(A, dataA);
    DrawChannel(B, dataB);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawChannel(Channel ch, uint8 data[FPGA_MAX_NUM_POINTS])
{
    int bottom = Grid::Bottom();
    int left = Grid::Left();

    if (!SET_ENABLED(ch))
    {
        return;
    }
    
    float scale = (float)Grid::Height() / 255.0f;

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
        
        uint8 dat1 = 0;
        uint8 dat2 = 0;
        
        float val1 = dat1 * scale;
        float val2 = dat2 * scale;
        
        float value = 0.0f;
        float valuePrev = 0.0f;
        
        for (int i = 1; i < 281; i++)
        {
            dat1 = data[i - 1];
            dat2 = data[i];
            
            val1 = dat1 * scale;
            val2 = dat2 * scale;
            
            value = bottom - dat2 * scale;
            valuePrev = bottom - dat1 * scale;
            Painter::DrawVLine(x++, valuePrev, value);
            
            if(dat1 < dat2 && ch == A)
            {
                dat1 = dat1;
            }
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
