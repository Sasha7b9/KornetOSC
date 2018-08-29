#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsTime Settings Time
 *  @{
 */

struct PeakDetMode
{
    enum E
    {
        Disabled,
        Enabled,
        Average
    } value;
    PeakDetMode(E v = Disabled) : value(v) {};
    PeakDetMode(uint v) : value((E)v) {};
    operator  uint8() const { return (uint8)value; };
};

struct TBase
{
    enum E
    {
        _2ns,
        _5ns,
        _10ns,
        _20ns,
        _50ns,
        _100ns,
        _200ns,
        _500ns,
        _1us,
        _2us,
        _5us,
        _10us,
        _20us,
        _50us,
        _100us,
        _200us,
        _500us,
        _1ms,
        _2ms,
        _5ms,
        _10ms,
        _20ms,
        _50ms,
        _100ms,
        _200ms,
        _500ms,
        _1s,
        _2s,
        _5,
        _10s,
        Size
    } value;
    TBase(E v = _2ns) : value(v) {};
    operator uint8() const { return (uint8)value; };
    pString Name() const;
};

#define SET_TSHIFT          (set.time_shift)
#define SET_TBASE           (set.time_base)
#define TIME_DIV_XPOS       (set.time_timeDivXPos)

#define SET_PEAKDET         (set.time_peakDet)
#define SET_PEAKDET_EN      (SET_PEAKDET == PeakDetMode::Enabled)
#define SET_PEAKDET_DIS     (SET_PEAKDET == PeakDetMode::Disabled)

#define IN_RANDOM_MODE      (SET_TBASE <= TBase::_50ns)
#define IN_P2P_MODE         (SET_TBASE >= MIN_TBASE_P2P)

#define TPOS                (set.time_TPos)
#define TPOS_IS_RIGHT       (TPOS == TPos::Right)
#define TPOS_IS_LEFT        (TPOS == TPos::Left)
#define TPOS_IS_CENTER      (TPOS == TPos::Center)

#define SAMPLE_TYPE         (set.time_sampleType)
#define SAMPLE_TYPE_IS_REAL (SAMPLE_TYPE == SampleType::Real)
#define SAMPLE_TYPE_OLD     (set.time_sampleTypeOld)

#define TPOS_IN_POINTS      sTime_TPosInPoints()
#define TSHIFT_IN_POINTS    sTime_TShiftInPoints()
#define TPOS_IN_BYTES       sTime_TPosInBytes()

#define LINKING_TSHIFT      (set.time_linkingTShift)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Сохранить масштаб по времени
void sTime_SetTBase(TBase tBase);
/// Сохранить смещение по времени в относительных единицах
void sTime_SetTShift(int16 shift);
/// Узнать привязку отсительно уровня синхронизации в байтах
int sTime_TPosInBytes();
/// Минимальное смещение по времени, которое может быть записано в аппаратную часть
int16 sTime_TShiftMin();
/// Смещение по времени, соответствующее позиции TPos
int16 sTime_TShiftZero();

int sTime_TShiftInPoints();

int sTime_TPosInPoints();


/** @}  @}
 */
