#include "defines.h"
#include "FrequencyCounter.h"
#include "FPGA/FPGA.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Utils/StringUtils.h"
#include "Utils/Values.h"
#include "Hardware/FSMC.h"
#include "Menu/Pages/Include/PageFunction.h"
#include "Utils/Stack.h"
#include "Utils/Math.h"
#include "Hardware/Timer.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BitSet32 FrequencyCounter::freqActual;
BitSet32 FrequencyCounter::periodActual;
bool     FrequencyCounter::readPeriod;
float    FrequencyCounter::prevFreq;
float    FrequencyCounter::frequency;
bool     FrequencyCounter::lampFreq = false;
bool     FrequencyCounter::lampPeriod = false;

//                         0    1    2    3    4    5    6 
static char buffer[11] = {'0', '0', '0', '0', '0', '0', '0', 0, 0, 0, 0};

BitSet32 FrequencyCounter::lastFreq;
BitSet32 FrequencyCounter::lastPeriod;
uint     FrequencyCounter::lastFreqRead = 0;
uint     FrequencyCounter::lastPeriodRead = 0;
uint     FrequencyCounter::lastFreqOver = 0;
uint     FrequencyCounter::lastPeriodOver = 0;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrequencyCounter::Init()
{
    LoadSettings();
    FSMC::WriteToFPGA8(WR_RESET_COUNTER_FREQ, 1);
    FSMC::WriteToFPGA8(WR_RESET_COUNTER_PERIOD, 1);
    freqActual.word = periodActual.word = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::LoadSettings()
{
    uint8 data = 0;

    if (FREQ_METER_IS_ENABLED)
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
void FrequencyCounter::LoadFreqSettings()
{
    LoadSettings();
    FSMC::WriteToFPGA8(WR_RESET_COUNTER_FREQ, 1);
    freqActual.word = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::LoadPeriodSettings()
{
    LoadSettings();
    FSMC::WriteToFPGA8(WR_RESET_COUNTER_PERIOD, 1);
    periodActual.word = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::Update(uint16 flag)
{
    SetStateLamps(flag);

    bool freqReady = _GET_BIT(flag, FPGA::Flag::FREQ_READY) == 1;

    if(freqReady)
    {
        lastFreqRead = TIME_MS;
    }

    bool periodReady = _GET_BIT(flag, FPGA::Flag::PERIOD_READY) == 1;

    if(periodReady)
    {
        lastPeriodRead = TIME_MS;
    }

    if (freqReady)
    {
        freqActual.Set(*RD_FREQ_BYTE_3, *RD_FREQ_BYTE_2, *RD_FREQ_BYTE_1, *RD_FREQ_BYTE_0);

        lastFreq.Set(freqActual.word);
        
        if (!readPeriod)
        {
            ReadFreq();
        }
    }

    if (periodReady)
    {
        periodActual.Set(*RD_PERIOD_BYTE_3, *RD_PERIOD_BYTE_2, *RD_PERIOD_BYTE_1, *RD_PERIOD_BYTE_0);

        lastPeriod.Set(periodActual.word);

        if (readPeriod)
        {
            ReadPeriod();
        }
    }

    if(_GET_BIT(flag, FPGA::Flag::FREQ_OVERFLOW) == 1)
    {
        freqActual.word = 0;
        lastFreqOver = TIME_MS;
    }
    if(_GET_BIT(flag, FPGA::Flag::PERIOD_OVERFLOW) == 1)
    {
        periodActual.word = 0;
        lastPeriodOver = TIME_MS;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::ReadFreq()
{
    BitSet32 freqSet(*RD_FREQ_BYTE_3, *RD_FREQ_BYTE_2, *RD_FREQ_BYTE_1, *RD_FREQ_BYTE_0);

    lastFreq.Set(freqSet.word);

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
    BitSet32 periodSet(*RD_PERIOD_BYTE_3, *RD_PERIOD_BYTE_2, *RD_PERIOD_BYTE_1, *RD_PERIOD_BYTE_0);

    lastPeriod.Set(periodSet.word);

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
    return FREQ_METER_IS_ENABLED ? (fr->word * k[FREQ_METER_TIMECOUNTING]) : (fr->word * 10.0f);
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

    return FREQ_METER_IS_ENABLED ? (k[FREQ_METER_FREQ_CLC] * kP[FREQ_METER_NUM_PERIODS] / (float)period_->word) : (10e5f / (float)period_->word);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float FrequencyCounter::GetFreq()
{
    return frequency;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::Draw()
{
    /// \todo ¬ этой строке точку ставить не где придЄтс€, а в той позиции, где она сто€ла последний раз

#define EMPTY_STRING "\xa9\xa9\xa9.\xa9\xa9\xa9"
#define SIZE 4

    if (!FREQ_METER_IS_ENABLED)
    {
        return;
    }

    int width = 241;
    int height = 74;
    int x = Grid::Left() + (Grid::Width() - width) / 2;
    int y = Grid::Top() + (Grid::Height() / 2 - height) / 2;

    
    Painter::FillRegion(x + 1,   y + 1, width - 2, height - 2, Color::BACK);
    Painter::DrawRectangle(x,    y,     width,     height,     Color::FILL);

    x += 2;
    y += 2;

    Painter::DrawBigText(x + 2,  y + 1,         SIZE, "F", Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceTimeF()));

    Painter::DrawRectangle(x - 20, y, 10, 10);
    if(lampFreq)
    {
        Painter::FillRegion(x - 20, y, 10, 10);
    }

    Painter::DrawBigText(x + 2,  y + 10 * SIZE, SIZE, "T", Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceNumPeriods()));

    Painter::DrawRectangle(x - 20, y + 10 * SIZE, 10, 10);
    if(lampPeriod)
    {
        Painter::FillRegion(x - 20, y + 10 * SIZE, 10, 10);
    }

    int dX = 7 * SIZE;
    Painter::DrawBigText(x + dX, y + 1,         SIZE, "=", Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceTimeF()));
    Painter::DrawBigText(x + dX, y + 10 * SIZE, SIZE, "=", Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceNumPeriods()));
    
    dX = SIZE * 12;

    Painter::DrawBigText(x + dX, y + 1, SIZE, (freqActual.word == 0) ? EMPTY_STRING : FreqSetToString(&freqActual),
                         Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceTimeF()));

    Painter::DrawBigText(x + dX, y + 10 * SIZE, SIZE, (periodActual.word == 0) ? EMPTY_STRING : PeriodSetToString(&periodActual),
                         Choice::ColorMenuField(PageFunction::PageFrequencyCounter::GetChoiceNumPeriods()));


    /*
    width = 50;
    height = 27;
    x = 50;
    y = 120;
    Painter::FillRegion(x, y, width, height, Color::BACK);
    Painter::DrawRectangle(x - 1, y - 1, width + 2, height + 2, Color::FILL);
    Painter::DrawFormatText(x + 4, y + 4, "%d", freqActual.word);
    Painter::DrawFormatText(x + 4, y + 15, "%d", periodActual.word);

    x += 100;
    width = 100;


    Painter::FillRegion(x, y, width, height, Color::BACK);
    Painter::DrawRectangle(x - 1, y - 1, width + 2, height + 2, Color::FILL);

    Painter::DrawFormatText(x + 4, y + 4, "%d", lastFreq.word);
    Painter::DrawFormatText(x + 4, y + 15, "%d", lastPeriod.word);

    int size = 8;

    x += 60;

#define TIME 250

    Painter::DrawRectangle(x, y + 4, size, size, Color::FILL);

    if(TIME_MS - lastFreqRead < TIME)
    {
        Painter::FillRegion(x + 1, y + 5, size - 2, size - 2, Color::BLUE);
    }

    Painter::DrawRectangle(x, y + 15, size, size, Color::FILL);

    if(TIME_MS - lastPeriodRead < TIME)
    {
        Painter::FillRegion(x + 1, y + 16, size - 2, size - 2, Color::BLUE);
    }

    x += 20;

    Painter::DrawRectangle(x, y + 4, size, size, Color::FILL);

    if(TIME_MS - lastFreqOver < TIME)
    {
        Painter::FillRegion(x + 1, y + 5, size - 2, size - 2, Color::RED);
    }

    Painter::DrawRectangle(x, y + 15, size, size, Color::FILL);

    if(TIME_MS - lastPeriodOver < TIME)
    {
        Painter::FillRegion(x + 1, y + 16, size - 2, size - 2, Color::RED);
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString FrequencyCounter::PeriodSetToString(const BitSet32 *pr)
{
    Hex value(pr->word);

    while(value.NumDigits() > 6)
    {
        value.Set(value / 10);
    }

    /*
    +----------+-----------+------------+------------+------------+
    | 1к√ц 1мс | 100 к√ц   | 1 ћ√ц      | 10 ћ√ц     | 100 ћ√ц    |
    +----------+-----------+------------+------------+------------+
    | 1        |    1e2    |     1e3    |     1e4    |     1e5    | - считанное значение
    |          |   1.00 мс |   1.000 мс |  1.0000 мс | 1.00000 мс | - представление на дисплее
    |          |    1e7    |     1e6    |     1e5    |     1e4    | - на какое число умножить, чтобы получить количество пикосекунд в считанном
    +----------+-----------+------------|------------+------------+   значении
    | 10       |    1e3    |     1e4    |     1e5    |     1e6    |
    |          |  1.000 мс |  1.0000 мс | 1.00000 мс | 1.00000 мс |
    |          |    1e6    |     1e5    |     1e4    |     1e3    |
    +----------+-----------+------------+------------+------------+
    | 100      |    1e4    |     1e5    |     1e6    |     1e7    |
    |          | 1.0000 мс | 1.00000 мс | 1.00000 мс | 1.00000 мс |
    |          |    1e5    |     1e4    |     1e3    |     1e2    |
    +----------+-----------+------------+------------+------------+
    */

    /*
    static const uint64 k[FrequencyCounter::NumberPeriods::Number][FrequencyCounter::FreqClc::Number] =
    {
        {10 * 1000 * 1000, 1000 * 1000, 100 * 1000, 10 * 1000},
        {     1000 * 1000,  100 * 1000,  10 * 1000,      1000},
        {      100 * 1000,   10 * 1000,       1000,       100}
    };
    */

    // ѕолучаем количество пикосекунд
    //    uint64 numPS = ticks * k[FREQ_METER_NUM_PERIODS][FREQ_METER_FREQ_CLC];

    /*
    »змер€емое значение | ѕринимаемое значение | ¬ывод на экран | последний значащий разр€д

    +----------+-------------------------------------+-------------------------------------+-------------------------------------+-------------------------------------+
    |          | 100 к√ц                    0        | 1 ћ√ц                      1        | 10 ћ√ц                     2        | 100 ћ√ц                    3        |
    +----------+-------------------------------------+-------------------------------------+-------------------------------------+-------------------------------------+
    | 1        | 10   мкс        1    0.01 мс  1e-5  | 1 мкс          1      1. мкс  1e-6  | 100 нс         1     0.1 мкс  1e-7  | 10  нс         1    0.01 мкс  1e-8  | 
    |          | 100  мкс       10    0.10 мс  1e-5  | 10 мкс        10     10. мкс  1e-6  | 1   мкс       10     1.0 мкс  1e-7  | 100 нс        10    0.10 мкс  1e-8  |
    |          | 1    мс       100    1.00 мс  1e-5  | 100 мкс      100    100. мкс  1e-6  | 10  мкс      100    10.0 мкс  1e-7  | 1   мкс      100    1.00 мкс  1e-8  |
    |          | 10   мс      1000   10.00 мс  1e-5  | 1   мс      1000   1.000 мс   1e-6  | 100 мкс     1000   100.0 мкс  1e-7  | 10  мкс     1000   10.00 мкс  1e-8  |
    |          | 100  мс     10000  100.00 мс  1e-5  | 10  мс     10000  10.000 мс   1e-6  | 1   мс     10000  1.0000 мс   1e-7  | 100 мкс    10000  100.00 мкс  1e-8  |
    |          | 1    с     100000 1.00000 с   1e-5  | 100 мс    100000 100.000 мс   1e-6  | 10  мс    100000 10.0000 мс   1e-7  | 1   мс    100000 1.00000 мс   1e-8  |
    |          | 10   с    100000- 10.0000 с   1e-4  | 1   с    100000- 1.00000 с    1e-5  | 100 мс   100000- 100.000 мс   1e-6  | 10  мc   100000- 10.0000 мс   1e-7  |
    |          | 100  с   100000-- 100.000 с   1e-3  | 10  с   100000-- 10.0000 с    1e-4  | 1   с   100000-- 1.00000 с    1e-5  | 100 мс  100000-- 100.000 мс   1e-6  |
    |        0 | 1000 с   переполнение               | 100 с   переполнение                | 10  с   переполнение                | 1   c   переполнение                |
    +----------+-------------------------------------+-------------------------------------|-------------------------------------+-------------------------------------+
    | 10       |                                     |                                     |                                     | 1   нс         1      1. нс   1e-9  |
    |          |                                     |                                     |                         /           | 10  нс        10     10. нс   1e-9  |
    |          |                                     |                                     |                     /               | 100 нс       100    100. нс   1e-9  |
    |          |                                     |                                     |                  /                  | 1   мкс     1000   1.000 мкс  1e-9  |
    |          |                                     |                                     |             /                       | 10  мкс    10000  10.000 мкс  1e-9  | 
    |          |                                     |                                     |         /                           | 100 мкс   100000 100.000 мкс  1e-9  | 
    |          |                                     |                                     |   |  /                              | 1   мс   100000- 1.00000 мс   1e-8  | 
    |          |                                     |                                     |   |---                              | 10  мс  100000-- 10.0000 мс   1e-7  |
    |        1 |                                     |                                     |                                     | 100 мс  переполнение                |
    +----------+-------------------------------------+-------------------------------------+-------------------------------------+-------------------------------------+
    | 100      |                                     |                                     |                                     | 0.1 нс         1     0.1 нс   1e-10 |
    |          |                                     |                                     |                           /         | 1   нс        10     1.0 нс   1e-10 |
    |          |                                     |                                     |                       /             | 10  нс       100    10.0 нс   1e-10 |
    |          |                                     |                                     |                    /                | 100 нс      1000   100.0 нс   1e-10 |
    |          |                                     |                                     |               /                     | 1   мкс    10000  1.0000 мкс  1e-10 |
    |          |                                     |                                     |           /                         | 10  мкс   100000 10.0000 мкс  1e-10 |
    |          |                                     |                                     |     |  /                            | 100 мкс  100000- 100.000 мкс  1e-9  |
    |          |                                     |                                     |     |---                            | 1   мс  100000-- 1.00000 мс   1e-8  |
    |        2 |                                     |                                     |                                     | 10  мс  переполнение                |
    +----------+-------------------------------------+-------------------------------------+-------------------------------------+-------------------------------------+
    */

    // —только насчитало импульсов за врем€ измерени€
    uint ticks = pr->word;

    for(int i = 0; i < 7; i++)
    {
        buffer[i] = value.DigitInPosition(6 - i);
    }

#define e3 (            1000)
#define e4 (       10 * 1000)
#define e5 (      100 * 1000)
#define e6 (     1000 * 1000)
#define e7 (10 * 1000 * 1000)

#define WRITE_SUFFIX(suffix)                        strcpy(buffer + 7, suffix);

#define WRITE_SUFFIX_2(value, suffix1, suffix2)     \
    if(ticks < value) WRITE_SUFFIX(suffix1)         \
    else              WRITE_SUFFIX(suffix2)

#define WRITE_SUFFIX_3(value1, value2, suffix1, suffix2, suffix3)   \
    if(ticks < value1)      WRITE_SUFFIX(suffix1)                   \
    else if(ticks < value2) WRITE_SUFFIX(suffix2)                   \
    else                    WRITE_SUFFIX(suffix3)

#define SET_POINT(pos)                              memcpy(buffer, buffer + 1, pos); buffer[pos] = '.';

#define CHOICE_4(v1, pos1, v2, pos2, v3, pos3, pos4) \
    if(ticks < v1)      { SET_POINT(pos1) }          \
    else if(ticks < v2) { SET_POINT(pos2) }          \
    else if(ticks < v3) { SET_POINT(pos3) }          \
    else                { SET_POINT(pos4) }

    switch(FREQ_METER_NUM_PERIODS + FREQ_METER_FREQ_CLC)
    {
        case 0:
            WRITE_SUFFIX_2(e5, "мс", "с");
            CHOICE_4(e5, 4, e6, 1, e7, 2, 3);
            break;
        case 1:
            WRITE_SUFFIX_3(e3, e6, "мкс", "мс", "c");
            CHOICE_4(e3, 6, e6, 3, e7, 1, 2);
            break;
        case 2:
            WRITE_SUFFIX_3(e4, e7, "мкс", "мс", "с");
            CHOICE_4(e4, 5, e6, 2, e7, 3, 1);
            break;
        case 3:
            WRITE_SUFFIX_2(e5, "мкс", "мс");
            CHOICE_4(e5, 4, e6, 1, e7, 2, 3);
            break;
        case 4:
            WRITE_SUFFIX_3(e3, e6, "нс", "мкс", "мс");
            CHOICE_4(e3, 6, e6, 3, e7, 1, 2);
            break;
        case 5:
            WRITE_SUFFIX_3(e4, e7, "нс", "мкс", "мс");
            CHOICE_4(e4, 5, e6, 2, e7, 3, 1);
            break;
    }

    return buffer;
}



//----------------------------------------------------------------------------------------------------------------------------------------------------
pString FrequencyCounter::FreqSetToString(const BitSet32 *fr)
{
    Hex value(fr->word);

    while(value.NumDigits() > 6)
    {
        value.Set(value / 10);
    }

    for(int i = 0; i < 7; i++)
    {
        buffer[i] = value.DigitInPosition(6 - i);
    }

    uint freq = fr->word;

    uint giverFreq = freq;

/// Ёто герцы * 10
#define E_2 (               100)
#define E_3 (              1000)
#define E_4 (         10 * 1000)
#define E_5 (        100 * 1000)
#define E_6 (       1000 * 1000)
#define E_7 (  10 * 1000 * 1000)
#define E_8 ( 100 * 1000 * 1000)
#define E_9 (1000 * 1000 * 1000)


#undef WRITE_SUFFIX
#define WRITE_SUFFIX(suffix_E4)    \
    if(giverFreq < E_4) { strcpy(buffer + 7, suffix_E4); } else if (giverFreq < E_7) { strcpy(buffer + 7, "к√ц"); } else { strcpy(buffer + 7, "ћ√ц"); }

#define HIGH_FREQ                       \
    if(giverFreq < E_8)                 \
    {                                   \
        memcpy(buffer, buffer + 1, 2);  \
        buffer[1] = '.';                \
    }                                   \
    else if (giverFreq < E_9)           \
    {                                   \
        memcpy(buffer, buffer + 1, 3);  \
        buffer[2] = '.';                \
    }                                   \
    else                                \
    {                                   \
        memcpy(buffer, buffer + 1, 3);  \
        buffer[3] = '.';                \
    }


    switch (FREQ_METER_TIMECOUNTING)
    {
        case FrequencyCounter::TimeCounting::_100ms:

            giverFreq *= 100;

            WRITE_SUFFIX("к√ц");

            if(giverFreq < E_7)                         // ћеньше 1 ћ√ц
            {
                if(freq >= E_2)                         // Ѕольше или равно 10 √ц
                {
                    memcpy(buffer, buffer + 1, 5);
                }
                buffer[4] = '.';
            }
            else
            {
                HIGH_FREQ;
            }            
            break;

        case FrequencyCounter::TimeCounting::_1s:

            giverFreq *= 10;

            WRITE_SUFFIX("√ц");

            if (giverFreq < E_7)                        // ћеньше 1 ћ√ц
            {
                if(giverFreq < E_4)                     // ћеньше 1 к√ц
                {
                    memcpy(buffer, buffer + 1, 6);
                    buffer[6] = '.';
                }
                else
                {
                    memcpy(buffer, buffer + 1, 4);
                    buffer[3] = '.';
                }
            }
            else
            {
                HIGH_FREQ;
            }
            break;

        case FrequencyCounter::TimeCounting::_10s:

            WRITE_SUFFIX("√ц");

            if (freq < E_7)                       // ћеньше 1 ћ√ц
            {
                if (giverFreq < E_4)             // ћеньше 1 к√ц
                {
                    memcpy(buffer, buffer + 1, 5);
                    buffer[5] = '.';
                }
                else
                {
                    memcpy(buffer, buffer + 1, 3);
                    buffer[2] = '.';
                }
            }
            else
            {
                HIGH_FREQ;
            }
            break;
        default:
            break;
    }

    return buffer;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::SetStateLamps(uint16 flag)
{
    SetStateLampFreq(flag);
    SetStateLampPeriod(flag);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::SetStateLampFreq(uint16 flag)
{
    if(!lampFreq)
    {
        if(_GET_BIT(flag, FPGA::Flag::FREQ_IN_PROCESS))
        {
            lampFreq = true;
        }
    }
    else
    {
        if(_GET_BIT(flag, FPGA::Flag::FREQ_READY))
        {
            lampFreq = false;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyCounter::SetStateLampPeriod(uint16 flag)
{
    if(!lampPeriod)
    {
        if(_GET_BIT(flag, FPGA::Flag::PERIOD_IN_PROCESS))
        {
            lampPeriod = true;
        }
    }
    else
    {
        if(_GET_BIT(flag, FPGA::Flag::PERIOD_READY))
        {
            lampPeriod = false;
        }
    }
}
