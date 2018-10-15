#include "FrequencyCounter.h"
#include "FPGA/FPGATypes.h"
#include "Settings/Settings.h"
#include "Display/Painter.h"
#include "Utils/StringUtils.h"


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

    *WR_FREQMETER = data;
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
void FrequencyCounter::Draw(int x, int y)
{
    if (!FREQ_METER_ENABLED)
    {
        return;
    }

#define EMPTY_STRING "---.---"

    int width = 68;
    int height = 19;

    Painter::FillRegion(x + 1, y + 1, width - 2, height - 2, Color::BACK);
    Painter::DrawRectangle(x, y, width, height, Color::Trig());

    Painter::DrawText(x + 2, y + 1, "F =");
    Painter::DrawText(x + 2, y + 10, "T");
    Painter::DrawText(x + 10, y + 10, "=");

    char buffer[30];
    float freq = FreqSetToFreq(&freqActual);

    bool condFreq = _SET_BIT(flag, FL_OVERFLOW_FREQ) == 1 || drawFreq == false || freq == 0.0f;

    Painter::DrawText(x + 17, y + 1, condFreq ? EMPTY_STRING : Freq2StringAccuracy(freq, buffer, 6));

    freq = PeriodSetToFreq(&periodActual);

    bool condPeriod = _GET_BIT(flag, FL_OVERFLOW_PERIOD) == 1 || drawPeriod == false || freq == 0.0f;

    Painter::SetColor(Color::Trig());
    Painter::DrawText(x + 17, y + 10, condPeriod ? EMPTY_STRING : Time2StringAccuracy(1.0f / freq, false, buffer, 6));

    /** @todo Последняя страка оставлена, потому что без неё получается артефакт изображения */
    Painter::DrawText(x + 71, y + 10, "");
}
