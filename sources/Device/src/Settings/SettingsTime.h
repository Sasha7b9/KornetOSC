﻿#pragma once


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
    pString ToString() const;
};

/// Тип привязки к смещению по горизонтали
struct LinkingTShift
{
    enum E
    {
        Time,     ///< Смещение привязано к времени
        Position  ///< Смещение привязано к позиции
    } value;
};

/// Функция ВР/ДЕЛ.
struct FunctionTime
{
    enum E
    {
        Time,
        ShiftInMemory
    } value;
};

/// Тип выборки для режима рандомизатора.
struct SampleType
{
    enum E
    {
        Real,    ///< реальное время - в построении участвуют только реально считанные точки, ничего не рассчитывается.
        Equal    ///< эквивалентная - сигнал строится по последним точкам, полученным от рандомизатора.
    } value;
    SampleType(E v) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

/// Положение точки синхронизация на сигнале.
struct TPos
{
    enum E
    {
        Left,          ///< Привязка к левому краю.
        Center,        ///< Привязка к центру.
        Right          ///< Привязка к правому краю.
    } value;
    operator uint8() const { return (uint8)value; };
    /// Узнать привязку отсительно уровня синхронизации в байтах
    //int sTime_TPosInBytes();
    int InBytes();
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

#define LINKING_TSHIFT      (set.time_linkingTShift)


/** @}  @}
 */
