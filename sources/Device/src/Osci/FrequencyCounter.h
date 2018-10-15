#pragma once


#define FREQ_METER_ENABLED              (set.freq_enabled)
#define FREQ_METER_IS_ENABLED           (FREQ_METER_ENABLED == FPGA::FreqMeter::Enabled::On)
#define FREQ_METER_TIMECOUNTING         (set.freq_timeCounting)
#define FREQ_METER_FREQ_CLC             (set.freq_freqClc)
#define FREQ_METER_NUM_PERIODS          (set.freq_numberPeriods)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FrequencyCounter
{
public:
    /// Инициализация. Должна производиться при каждом изменении настроек
    static void Init();

    static void Update(uint16 flag);
    /// Возвращает измеренное значение частоты
    static float GetFreq();
    /// Отрисовка значения
    static void Draw(int x, int y);

    /// Время счёта периода.
    struct TimeCounting
    {
        enum E
        {
            _100ms,
            _1s,
            _10s
        } value;
        operator uint8() const
        {
            return (uint8)value;
        }
    };

    /// Частота заполняющих импульсов для счёта частоты.
    struct FreqClc
    {
        enum E
        {
            _100kHz,
            _1MHz,
            _10MHz,
            _100MHz
        } value;
        operator uint8() const
        {
            return (uint8)value;
        }
    };

    /// Количество периодов.
    struct NumberPeriods
    {
        enum E
        {
            _1,
            _10,
            _100
        } value;
        operator uint8() const
        {
            return (uint8)value;
        }
    };

    struct Enabled
    {
        enum E
        {
            On,
            Off
        } value;
        operator uint8() const
        {
            return (uint8)value;
        }
    };

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

    static uint16 flag;
};
