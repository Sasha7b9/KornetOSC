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
#include "Data/Reader.h"
#include "Symbols.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StructDataDrawing *PainterData::dataStruct = 0;


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

    DrawMemoryWindow();
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawMemoryWindow()
{
    static const int rightXses[3] = {276, 285, 247};
    int rightX = rightXses[MODE_WORK];
    if (sCursors_NecessaryDrawCursors())
    {
        rightX = 68;
    }

    if (DS)
    {
        DrawDataInRect(rightX + 2, LAST_AFFECTED_CH_IS_A ? B : A);
        DrawDataInRect(rightX + 2, LAST_AFFECTED_CH_IS_A ? A : B);
    }

    int leftX = 3;
    float scaleX = (float)(rightX - leftX + 1) / SET_POINTS_IN_CHANNEL;
    const int xVert0 = leftX + (int)(SHIFT_IN_MEMORY_IN_POINTS * scaleX);
    int width = (int)((rightX - leftX) * (282.0f / SET_POINTS_IN_CHANNEL));
    Painter::DrawRectangle(xVert0, 0, width - (FPGA_POINTS_8k ? 1 : 0), Grid::Top() - 2, Color::FILL);

    DrawTPos(leftX, rightX);

    DrawTShift(leftX, rightX, NUM_BYTES_SET);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawDataInRect(int width, Channel ch)
{
    if (!dataStruct->needDraw[ch])
    {
        return;
    }

    uint8 *data = OUT(ch);

    float elemsInColumn = NUM_BYTES_SET / (float)width;

#undef SIZE_BUFFER
#define SIZE_BUFFER 300
    uint8 min[SIZE_BUFFER];
    uint8 max[SIZE_BUFFER];

    if (PEAKDET_DS != PeakDet_Disabled)                                 // Если пик. дет. включен
    {
        uint8 *iMin = &min[0];
        uint8 *iMax = &max[0];

        for (int col = 0; col < width; col++, iMin++, iMax++)
        {
            uint firstElem = (uint)(col * elemsInColumn);
            uint lastElem = (uint)(firstElem + elemsInColumn - 1);
            *iMin = data[firstElem];
            *iMax = data[firstElem];
            for (uint elem = firstElem + 1; elem <= lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], *iMin);
                SET_MAX_IF_LARGER(data[elem], *iMax);
            }
        }
    }
    else                                                                // Если пик. дет. выключён
    {
        for (int col = 0; col < width; col++)
        {
            uint firstElem = (uint)(col * elemsInColumn);
            uint lastElem = (uint)(firstElem + elemsInColumn - 1);
            min[col] = data[firstElem];
            max[col] = data[firstElem];
            for (uint elem = firstElem + 1; elem <= lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], min[col]);
                SET_MAX_IF_LARGER(data[elem], max[col]);
            }
        }
    }

    int mines[SIZE_BUFFER];     // Массив для максимальных значений в каждом столбике
    int maxes[SIZE_BUFFER];     // Массив для минимальных значений в каждом столбике

    float scale = 17.0f / (MAX_VALUE - MIN_VALUE);

    mines[0] = Ordinate(max[0], scale);
    maxes[0] = Ordinate(min[0], scale);

    for (int i = 1; i < width; i++)
    {
        maxes[i] = Ordinate((uint8)((max[i] < min[i - 1]) ? min[i - 1] : max[i]), scale);
        mines[i] = Ordinate((uint8)((min[i] > max[i - 1]) ? max[i - 1] : min[i]), scale);
    }

    //*** Теперь определим количество точек, которые нужно нарисовать
    int numPoints = 0;
    for (int i = 0; i < width; ++i)
    {
        if (maxes[i] != -1 && mines[i] != -1) { numPoints++; }
    }

    numPoints--;

    //*** Теперь определим, с какой позиции выводить точки (если сигнал сжат по горизонтали, то вначале будет пустое место
    int x = 1;
    for (int i = 0; i < width; ++i)
    {
        if (maxes[i] == -1 && mines[i] == -1) { ++x; }
        else { break; }
    }

    if (numPoints > 1)
    {
        int delta = x;
        if (numPoints < 256)
        {
            SendToDisplayDataInRect(ch, x, mines + delta, maxes + delta, numPoints);
        }
        else
        {
            SendToDisplayDataInRect(ch, x, mines + delta, maxes + delta, 255);
            numPoints -= 255;
            SendToDisplayDataInRect(ch, x + 255, mines + 255 + delta, maxes + 255 + delta, numPoints);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawTPos(int leftX, int rightX)
{
    int x[] = {leftX, (rightX - leftX) / 2 + leftX, rightX};
    int x0 = x[TPOS];
    Painter::FillRegion(x0 - 3, 10, 6, 6, Color::BACK);
    Painter::DrawChar(x0 - 3, 10, SYMBOL_TPOS_1, Color::FILL);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::DrawTShift(int leftX, int rightX, int numBytes)
{
    float scale = (float)(rightX - leftX + 1) / ((float)numBytes - (numBytes == 281 ? 1 : 0));
    int xShift = (int)(1.5f + (TPOS_IN_BYTES - TSHIFT_IN_POINTS) * scale) - 1;
    if (SET_PEAKDET_EN && TPOS_IS_RIGHT)
    {
        --xShift;
    }
    if (FPGA_POINTS_512)
    {
        ++xShift;                           /// \todo Костыль
    }
    LIMIT_ABOVE(xShift, rightX - 2);

    int dX01 = 1, dX02 = 2, dX11 = 3, dY11 = 7, dY12 = 6;

    if (xShift < leftX - 2)
    {
        xShift = leftX - 2;
        dX01 = 3; dX02 = 1; dY12 = 6;
    }
    else if (xShift > rightX - 1)
    {
        xShift = rightX - 2;
        dX11 = 1;
    }
    else
    {
        dY11 = 5; dY12 = 7;
    }

    Painter::FillRegion((int)xShift - 1, 1, 6, 6, Color::BACK);
    Painter::FillRegion((int)xShift, 2, 4, 4, Color::FILL);
    Painter::DrawLine((int)xShift + dX01, 3, (int)xShift + dX11, dY11 - 2, Color::BACK);
    Painter::DrawLine((int)xShift + dX02, 4, (int)xShift + 2, dY12 - 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int PainterData::Ordinate(uint8 x, float scale)
{
    if (x == NONE_VALUE)
    {
        return -1;
    }

    LimitationRet<uint8>((uint8)(x - MIN_VALUE), 0, (MAX_VALUE - MIN_VALUE));

    return (int)((17.0f - scale * x) + 0.5f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData::SendToDisplayDataInRect(Channel ch, int x, int *min, int *max, int width)
{
    LIMIT_ABOVE(width, 255);

#undef SIZE_BUFFER
#define SIZE_BUFFER (255 * 2)
    uint8 points[SIZE_BUFFER];

    for (int i = 0; i < width; i++)
    {
        points[i * 2] = (uint8)max[i];
        points[i * 2 + 1] = (uint8)(min[i] < 0 ? 0 : min[i]);
    }

    Painter::DrawVLineArray(x, (int)width, points, Color::Chan(ch));
}
