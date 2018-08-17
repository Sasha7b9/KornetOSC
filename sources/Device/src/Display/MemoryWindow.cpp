#include "defines.h"
#include "MemoryWindow.h"
#include "Grid.h"
#include "Painter.h"
#include "Data/Storage.h"
#include "Data/Reader.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemoryWindow::Draw()
{
    int width = 278;
    int height = Grid::Top() - 2;

    uint8 *data[2];

    Storage::GetData(&data[0], &data[1]);

    Chan chans[2] = {LAST_AFFECTED_CH_IS_A ? Chan(Chan::B) : Chan(Chan::A), LAST_AFFECTED_CH_IS_A ? Chan(Chan::A) : Chan(Chan::B)};

    for (int i = 0; i < 2; i++)
    {
        Chan chan = chans[i];
        if (SET_ENABLED(chan))
        {
            Painter::SetColor(Color::Channel(chan));
            DrawDataInRect(0, 0, width, height, OUT(chan), FPGA_NUM_POINTS);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MemoryWindow::DrawDataInRect(int x, int y, int width, int height, uint8 *data, int length)
{
    int numIntervals = width + 1;            //  оличество интервалов, в которых будем рисовать наш сигнал - фактически, количество вертикальных линий
    float pointsInInterval = (float)length / numIntervals;   //  оличество точек, рисуемых в одном интервале.

    float stepY = (float)height / (float)(MAX_VALUE - MIN_VALUE);

    int y0 = y + height;

    for (int i = 0; i < numIntervals - 1; i++)
    {
        int start = (int)(i * pointsInInterval + 0.5f);          // Ќачальна€ точка в интервале
        int end = (int)((i + 1) * pointsInInterval + 0.5f) - 1;  //  онечна€ точка в интервале

        int min = 255;
        int max = 0;

        for (int j = start; j <= end; j++)
        {
            if (data[j] < min)
            {
                min = data[j];
            }
            if (data[j] > max)
            {
                max = data[j];
            }
        }

        Painter::DrawVLine(x + i, y0 - (int)(min * stepY + 0.5f), y0 - (int)(max * stepY + 0.5f));
    }
}
