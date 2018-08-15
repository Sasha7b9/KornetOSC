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
    if(MODE_WORK_IS_DIR)
    {
        DrawData_ModeDir();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawData_ModeDir()
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
    int center = (Grid::Bottom() - Grid::Top()) / 2;
    int left = Grid::Left();

    if (!SET_ENABLED(ch))
    {
        return;
    }
    
    float scale = (float)Grid::Height() / (MAX_VALUE - MIN_VALUE);

    if (MODE_DRAW_SIGNAL_IS_LINES)
    {
        if (THICKNESS_SIGNAL_IS_3)
        {
            Painter::SetColor(Color::ChanHalf(ch));

            int x = left;

            for (int i = 1; i < 281; i++)
            {
                int value = (int)(center - (data[i] - AVE_VALUE) * scale + 0.5f);
                int valuePrev = (int)(center - (data[i - 1] - AVE_VALUE) * scale + 0.5f);

                if (value == valuePrev)
                {
                    Painter::DrawHLine(value, x - 1, x + 1);
                    Painter::DrawVLine(x++, value - 1, value + 1);
                }
                else
                {
                    if(valuePrev > value)   { ++value;  }
                    else                    { --value;  }

                    if(valuePrev < value)
                    {
                        Swap(&valuePrev, &value);
                    }

                    Painter::DrawVLine(x - 1, value, valuePrev);
                    Painter::DrawVLine(x + 1, value, valuePrev);
                    Painter::DrawVLine(x++, valuePrev + 1, value - 1);
                }
            }
        }

        Painter::SetColor(Color::Chan(ch));

        int x = left;
               
        for (int i = 1; i < 281; i++)
        {
            int value = (int)(center - (data[i] - AVE_VALUE) * scale + 0.5f);
            int valuePrev = (int)(center - (data[i - 1] - AVE_VALUE) * scale + 0.5f);

            if(value == valuePrev)
            {
                Painter::SetPoint(x++, valuePrev);
            }
            else
            {
                Painter::DrawVLine(x++, valuePrev, valuePrev > value ? (value + 1) : (value - 1));
            }
        }
    }
    else
    {
        Painter::SetColor(Color::Chan(ch));

        for (int i = 0; i < 280; i++)
        {
            float value = center - (data[i] - AVE_VALUE) * scale;
            Painter::SetPoint(left + i, (uint8)ROUND(value));
        }
    }
}
