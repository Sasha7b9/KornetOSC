#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsMeasures Settings Measures
 *  @{
 */

struct MeasSource
{
    enum E
    {
        A,
        B,
        A_B
    } value;
    operator uint8() const { return (uint8)value; };
};

#define MODE_VIEW_SIGNALS               (set.meas_modeViewSignals) 
#define MODE_VIEW_SIGNALS_IS_COMPRESS   (MODE_VIEW_SIGNALS == ModeViewSignals::Compress)  // ������� �� ����� ��� ������ ���������
#define MEASURE(n)                      (set.meas_measures[n])
/// ����� �� �������� �������������� ���������
#define SHOW_MEASURES                   (set.meas_show)
#define MEAS_MARKED                     (set.meas_marked)
/// �� ����� ���� ����� ������ ��� ������������ �������������� ���������
#define MEAS_ZONE                       (set.meas_Zone)
/// ������ ��� �������������� ��������� ����� �� ����, ���������� �������
#define MEAS_ZONE_HAND                  (MEAS_ZONE == MeasuresZone_Hand)

#define NUM_MEASURES                    (set.meas_number)
#define NUM_MEASURES_IS_1_5             (NUM_MEASURES == MeasuresNumber::_1_5)
#define NUM_MEASURES_IS_2_5             (NUM_MEASURES == MeasuresNumber::_2_5)
#define NUM_MEASURES_IS_3_5             (NUM_MEASURES == MeasuresNumber::_3_5)
#define NUM_MEASURES_IS_6_1             (NUM_MEASURES == MeasuresNumber::_6_1)
#define NUM_MEASURES_IS_6_2             (NUM_MEASURES == MeasuresNumber::_6_2)

/// �� ������ ������ ����������� �������������� ���������
#define SOURCE_MEASURE                  (set.meas_source)

/// �������������� ��������� ������������ �� ������ 1
#define SOURCE_MEASURE_IS_A             (SOURCE_MEASURE == MeasSource::A)
/// �������������� ��������� ������������ �� ������ 2
#define SOURCE_MEASURE_IS_B             (SOURCE_MEASURE == MeasSource::B)
/// �������������� ��������� ������������ �� ����� �������
#define SOURCE_MEASURE_IS_A_B           (SOURCE_MEASURE == MeasSource::A_B)

#define POS_MEAS_CUR_U(n)               (set.meas_PosCurU[n])
#define POS_MEAS_CUR_U_0                (POS_MEAS_CUR_U(0))
#define POS_MEAS_CUR_U_1                (POS_MEAS_CUR_U(1))

#define POS_MEAS_CUR_T(n)               (set.meas_PosCurT[n])
#define POS_MEAS_CUR_T_0                (POS_MEAS_CUR_T(0))
#define POS_MEAS_CUR_T_1                (POS_MEAS_CUR_T(1))

/** @}  @}
 */
