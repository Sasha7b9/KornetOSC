#pragma once


#define FREQ_METER_ENABLED              (set.freq_enabled)
#define FREQ_METER_IS_ENABLED           (FREQ_METER_ENABLED.value == FrequencyCounter::Enabled::On)
#define FREQ_METER_TIMECOUNTING         (set.freq_timeCounting)
#define FREQ_METER_FREQ_CLC             (set.freq_freqClc)
#define FREQ_METER_NUM_PERIODS          (set.freq_numberPeriods)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FrequencyCounter
{
public:
    /// �������������. ������ ������������� ��� ������ ��������� ��������
    static void Init();

    static void Update(uint16 flag);
    /// ���������� ���������� �������� �������
    static float GetFreq();
    /// ��������� ��������
    static void Draw();

    /// ����� ����� �������.
    struct TimeCounting
    {
        enum E
        {
            _100ms,
            _1s,
            _10s
        } value;
        operator uint8() const { return (uint8)value; }
    };

    /// ������� ����������� ��������� ��� ����� �������.
    struct FreqClc
    {
        enum E
        {
            _100kHz,
            _1MHz,
            _10MHz,
            _100MHz,
            Number
        } value;
        operator uint8() const { return (uint8)value; }
    };

    /// ���������� ��������.
    struct NumberPeriods
    {
        enum E
        {
            _1,
            _10,
            _100,
            Number
        } value;
        operator uint8() const { return (uint8)value; }
    };

    struct Enabled
    {
        enum E
        {
            Off,
            On
        } value;
        uint8 ToUINT8() const { return (uint8)value; };
    };

private:

    static void ReadFreq();

    static void ReadPeriod();

    static float FreqSetToFreq(const BitSet32 *fr);

    static pString FreqSetToString(const BitSet32 *fr);

    static float PeriodSetToFreq(const BitSet32 *period);

    static pString PeriodSetToString(const BitSet32 *pr);
    /// ����� �������� ��������� �������������� �������� �������. ��� ������ � ������ �����������. 0 ��������, ��� �������� �������� �� ����
    static BitSet32 freqActual;
    /// ����� �������� ��������� �������������� �������� �������. ��� ������ � ������ �����������. 0 ��������, ��� �������� �������� �� ����
    static BitSet32 periodActual;
    /// ������������� � true �������� ��������, ��� ������� ����� ������� �� �������� �������
    static bool readPeriod;

    static float prevFreq;

    static float frequency;

    static float period;
};
