#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsMeasures Settings Measure
 *  @{
 */

/// —жимать ли сигналы при выводе измерений.
struct ModeViewSignals
{
    enum E
    {
        AsIs,       ///< ѕоказывать сигналы как есть.
        Compress    ///< —жимать сетку с сигналами.
    } value;
    operator uint8() const { return (uint8)value; };
};

#define MODE_VIEW_SIGNALS               (set.meas_modeViewSignals) 
#define MODE_VIEW_SIGNALS_IS_COMPRESS   (MODE_VIEW_SIGNALS == ModeViewSignals::Compress)  // —жимать ли сетку при выводе измерений
//#define MEASURE(n)                      (set.meas_measures[n])
/// Ќужно ли выводить автоматические измерени€
#define SHOW_MEASURES                   (set.meas_show)
#define MEAS_MARKED                     (set.meas_marked)
/// »з какой зоны брать сигнал дл€ произведени€ автоматических измерений
#define MEAS_ZONE                       (set.meas_Zone)
/// ƒанные дл€ автоматических измерений брать из зоны, задаваемой вручную
#define MEAS_ZONE_HAND                  (MEAS_ZONE == MeasuresZone_Hand)

#define NUM_MEASURES                    (set.meas_number)
#define NUM_MEASURES_IS_1_5             (NUM_MEASURES == Measure::OnDisplay::_1_5)
#define NUM_MEASURES_IS_2_5             (NUM_MEASURES == Measure::OnDisplay::_2_5)
#define NUM_MEASURES_IS_3_5             (NUM_MEASURES == Measure::OnDisplay::_3_5)
#define NUM_MEASURES_IS_6_1             (NUM_MEASURES == Measure::OnDisplay::_6_1)
#define NUM_MEASURES_IS_6_2             (NUM_MEASURES == Measure::OnDisplay::_6_2)

#define POS_MEAS_CUR_U(n)               (set.meas_PosCurU[n])
#define POS_MEAS_CUR_U_0                (POS_MEAS_CUR_U(0))
#define POS_MEAS_CUR_U_1                (POS_MEAS_CUR_U(1))

#define POS_MEAS_CUR_T(n)               (set.meas_PosCurT[n])
#define POS_MEAS_CUR_T_0                (POS_MEAS_CUR_T(0))
#define POS_MEAS_CUR_T_1                (POS_MEAS_CUR_T(1))

/** @}  @}
 */
