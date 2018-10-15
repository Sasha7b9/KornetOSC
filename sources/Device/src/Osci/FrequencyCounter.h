#pragma once
#include "defines.h"
#include "structs.h"


#define FREQ_METER_ENABLED              (set.freq_enabled)
#define FREQ_METER_IS_ENABLED           (FREQ_METER_ENABLED == FPGA::FreqMeter::Enabled::On)
#define FREQ_METER_TIMECOUNTING         (set.freq_timeCounting)
#define FREQ_METER_FREQ_CLC             (set.freq_freqClc)
#define FREQ_METER_NUM_PERIODS          (set.freq_numberPeriods)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FrequencyCounter
{
public:
    static void Update(uint8 flag);

private:

    static void ReadFreq();

    static void ReadPeriod();

    static float FreqSetToFreq(const BitSet32 *fr);

    static float PeriodSetToFreq(const BitSet32 *period);
    /// Здесь хранится последнее действительное значение частоты. Для вывода в режиме частотомера
    static BitSet32 freqActual;
    /// Здесь хранится последнее действительное значение периода. Для вывода в режиме частотомера
    static BitSet32 freqSet;

    static BitSet32 periodSet;

    static BitSet32 periodActual;

    static bool drawFreq;
    
    static bool drawPeriod;
    /// Установленное в true значение означает, что частоту нужно считать по счётчику периода
    static bool readPeriod;

    static float prevFreq;

    static float frequency;

    static float period;
};
