#include "defines.h"
#include "FrequencyCounter.h"
#include "FPGA/FPGATypes.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Utils/StringUtils.h"
#include "Utils/Values.h"
#include "Hardware/FSMC.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BitSet32 FrequencyCounter::freqActual;
BitSet32 FrequencyCounter::freqSet;
BitSet32 FrequencyCounter::periodActual;
BitSet32 FrequencyCounter::periodSet;
bool     FrequencyCounter::drawFreq;
bool     FrequencyCounter::drawPeriod;
bool     FrequencyCounter::readPeriod;
float    FrequencyCounter::prevFreq;
float    FrequencyCounter::frequency;
uint16   FrequencyCounter::flag;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrequencyCounter::Init()
{
    drawFreq = false;
    drawPeriod = false;

    uint8 data = 0;

    if (FREQ_METER_ENABLED)
    {
        const uint16 maskTime[3] = {0, 1, 2};
        const uint16 maskFreqClc[4] = {0, (1 << 2), (1 << 3), ((1 << 3) + (1 << 2))};
        const uint16 maskPeriods[3] = {0, (1 << 4), (1 << 5)};

        data |= maskTime[FREQ_METER_TIMECOUNTING];
        data |= maskFreqClc[FREQ_METER_FREQ_CLC];
        data |= maskPeriods[FREQ_METER_NUM_PERIODS];
    }
    else
    {
        _SET_BIT(data, 2);
    }

    FSMC::WriteToFPGA8(WR_FREQMETER, data);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::Update(uint16 flag_)
{
    flag = flag_;

    bool freqReady = _GET_BIT(flag, FL_FREQ_READY) == 1;
    bool periodReady = _GET_BIT(flag, FL_PERIOD_READY) == 1;

    if (freqReady)
    {
        freqActual.Set(*RD_FREQ_BYTE_3, *RD_FREQ_BYTE_2, *RD_FREQ_BYTE_1, *RD_FREQ_BYTE_0);
        
        drawFreq = true;

        if (!readPeriod)
        {
            ReadFreq();
        }
    }

    if (periodReady)
    {
        periodActual.Set(*RD_PERIOD_BYTE_3, *RD_PERIOD_BYTE_2, *RD_PERIOD_BYTE_1, *RD_PERIOD_BYTE_0);

        drawPeriod = true;

        if (readPeriod)
        {
            ReadPeriod();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::ReadFreq()
{
    freqSet.Set(*RD_FREQ_BYTE_3, *RD_FREQ_BYTE_2, *RD_FREQ_BYTE_1, *RD_FREQ_BYTE_0);

    if (freqSet.word < 1000)
    {
        readPeriod = true;
    }
    else
    {
        float fr = FreqSetToFreq(&freqSet);
        if (fr < prevFreq * 0.9f || fr > prevFreq * 1.1f)
        {
            frequency = ERROR_VALUE_FLOAT;
        }
        else
        {
            frequency = fr;
        }
        prevFreq = fr;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::ReadPeriod()
{
    periodSet.Set(*RD_PERIOD_BYTE_3, *RD_PERIOD_BYTE_2, *RD_PERIOD_BYTE_1, *RD_PERIOD_BYTE_0);

    float fr = PeriodSetToFreq(&periodSet);
    if (fr < prevFreq * 0.9f || fr > prevFreq * 1.1f)
    {
        frequency = ERROR_VALUE_FLOAT;
    }
    else
    {
        frequency = fr;
    }
    prevFreq = fr;
    readPeriod = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float FrequencyCounter::FreqSetToFreq(const BitSet32 *fr)
{
    const float k[3] = {10.0f, 1.0f, 0.1f};
    return FREQ_METER_ENABLED ? (fr->word * k[FREQ_METER_TIMECOUNTING]) : (fr->word * 10.0f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float FrequencyCounter::PeriodSetToFreq(const BitSet32 *period_)
{
    if (period_->word == 0)
    {
        return 0.0f;
    }

    const float k[4] = {10e4f, 10e5f, 10e6f, 10e7f};
    const float kP[3] = {1.0f, 10.0f, 100.0f};

    return FREQ_METER_ENABLED ? (k[FREQ_METER_FREQ_CLC] * kP[FREQ_METER_NUM_PERIODS] / (float)period_->word) : (10e5f / (float)period_->word);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float FrequencyCounter::GetFreq()
{
    return frequency;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::Draw()
{
#define EMPTY_STRING "---.---"
#define SIZE 4


    if (!FREQ_METER_ENABLED)
    {
        return;
    }

    int width = 241;
    int height = 74;
    int x = Grid::Left() + (Grid::Width() - width) / 2;
    int y = Grid::Top() + (Grid::Height() / 2 - height) / 2;

    
    Painter::FillRegion(x + 1,   y + 1, width - 2, height - 2, Color::BACK);
    Painter::DrawRectangle(x,    y,     width,     height,     Color::Trig());

    x += 2;
    y += 2;

    Painter::DrawBigText(x + 2,  y + 1,         SIZE, "F");
    Painter::DrawBigText(x + 2,  y + 10 * SIZE, SIZE, "T");
    int dX = 7 * SIZE;
    Painter::DrawBigText(x + dX, y + 10 * SIZE, SIZE, "=");
    Painter::DrawBigText(x + dX, y + 1,         SIZE, "=");
    
    char buffer[30];
    float freq = FreqSetToFreq(&freqActual);

    bool condFreq = _SET_BIT(flag, FL_OVERFLOW_FREQ) == 1 || drawFreq == false || freq == 0.0f;

    dX = SIZE * 12;

    Painter::DrawBigText(x + dX, y + 1, SIZE, condFreq ? EMPTY_STRING : FreqSetToString(&freqActual));

    freq = PeriodSetToFreq(&periodActual);

    bool condPeriod = _GET_BIT(flag, FL_OVERFLOW_PERIOD) == 1 || drawPeriod == false || freq == 0.0f;

    Painter::SetColor(Color::Trig());
    Painter::DrawBigText(x + dX, y + 10 * SIZE, SIZE, condPeriod ? EMPTY_STRING : Time(1.0f / freq).ToStringAccuracy(false, buffer, 6));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString FrequencyCounter::FreqSetToString(const BitSet32 *fr)
{
    Hex value(fr->word);

    switch (FREQ_METER_TIMECOUNTING)
    {
        case FrequencyCounter::TimeCounting::_100ms: value.Set(value * 100); break;
        case FrequencyCounter::TimeCounting::_1s:    value.Set(value * 10);  break;
        case FrequencyCounter::TimeCounting::_10s:                           break;
        default:                                                             break;
    }

    // ¬ этой точке в value хранитс€ завышенное в 10 раз значение частоты
    /// \todo сделать локализацию

    //                         0    1    2    3    4    5    6 
    static char buffer[11] = {'0', '0', '0', '0', '0', '0', '0'};

    for (int i = 0; i < 11; i++)
    {
        buffer[i] = '0';
    }
    buffer[10] = '\0';

    if (value < 10)                                                              // «начение меньше 1 √ц
    {
        buffer[5] = '.';
        buffer[6] = value.DigitInPosition(0);
        strcpy(buffer + 7, "√ц");
    }
    else if (value < 10000)                                                      // «начение меньше 1к√ц
    {
        buffer[6] = '.';
        buffer[5] = value.DigitInPosition(1);
        buffer[4] = value.DigitInPosition(2);
        buffer[3] = value.DigitInPosition(3);
        strcpy(buffer + 7, "√ц");
    }
    else if (value < 1000 * 10000)                                               // «начение меньше 1ћ√ц
    {
        buffer[6] = value.DigitInPosition(1);
        buffer[5] = value.DigitInPosition(2);
        buffer[4] = value.DigitInPosition(3);
        buffer[3] = '.';
        buffer[2] = value.DigitInPosition(4);
        buffer[1] = value.DigitInPosition(5);
        buffer[0] = value.DigitInPosition(6);
        strcpy(buffer + 7, "к√ц");
    }
    else
    {
        Frequency((float)(value / 10)).ToStringAccuracy(buffer, 6);
    }

    return buffer;
}
