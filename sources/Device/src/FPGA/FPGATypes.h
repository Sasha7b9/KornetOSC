#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


#define ADDR_ALTERA         ((uint8*)NOR_MEMORY_ADRESS1)


// ������ �������
#define WR_START            (ADDR_ALTERA + 0)           ///< �����
#define WR_TBASE            (ADDR_ALTERA + 1)           ///< ��������
#define WR_PRED_LO          (ADDR_ALTERA + 2)           ///< ����������
#define WR_PRED_HI          (ADDR_ALTERA + 3)
#define WR_POST_LO          (ADDR_ALTERA + 4)           ///< �����������
#define WR_POST_HI          (ADDR_ALTERA + 5)

#define WR_UPR              (ADDR_ALTERA + 6)           ///< ����������
#define BIT_UPR_RAND        0                           ///< ���. ������������
#define BIT_UPR_PEAK        1                           ///< ������� ��������
#define BIT_UPR_CALIBR      2                           ///< ����������

#define WR_FREQMETER        (ADDR_ALTERA + 7)           ///< ���������� ������������
#define WR_TRIG             (ADDR_ALTERA + 9)           ///< ���������� ��������������/��������
#define WR_START_ADDR       (ADDR_ALTERA + 11)          ///< \brief ����� ������. ����� ����������� �� ����� ������, ����� ������ ������ � 
                                                        ///  ������������� ������ (������� �� ���������� � ����������)

#define RD_DATA_A           (ADDR_ALTERA + 0)           ///< ������ ������� ������
#define RD_ADC_A            ((uint16 *)(RD_DATA_A))
#define RD_DATA_A_PEAK_MAX  (RD_DATA_A)                 ///< ������ �������� ��������� ������� ������
#define RD_DATA_A_PEAK_MIN  (RD_DATA_A_PEAK_MAX + 1)
#define RD_DATA_B           (ADDR_ALTERA + 2)           ///< ������ ������� ������
#define RD_ADC_B            ((uint16 *)(RD_DATA_B))
#define RD_DATA_B_PEAK_MAX  (RD_DATA_B)                 ///< ������ ������� ��������� ������� ������
#define RD_DATA_B_PEAK_MIN  (RD_DATA_B_PEAK_MAX + 1)
#define RD_LAST_RECORD_LO   (ADDR_ALTERA + 4)           ///< ����� ��������� ������
#define RD_LAST_RECORD_HI   (ADDR_ALTERA + 5)
#define RD_FREQ_BYTE_0      (ADDR_ALTERA + 8)           ///< ���������� �������� �������
#define RD_FREQ_BYTE_1      (ADDR_ALTERA + 9)
#define RD_FREQ_BYTE_2      (ADDR_ALTERA + 12)
#define RD_FREQ_BYTE_3      (ADDR_ALTERA + 13)
#define RD_PERIOD_BYTE_0    (ADDR_ALTERA + 16)          ///< ���������� �������� �������
#define RD_PERIOD_BYTE_1    (ADDR_ALTERA + 17)
#define RD_PERIOD_BYTE_2    (ADDR_ALTERA + 20)
#define RD_PERIOD_BYTE_3    (ADDR_ALTERA + 21)
#define RD_FLAG_LO          (ADDR_ALTERA + 24)          ///< ����
#define BIT_FLAG_DATA_READY 0                           ///< ������ ������ ��� ����������
#define BIT_FLAG_PRED       2                           ///< ���� 1, �� ���������� ��������, ����� ������ �������������� ������

#define FL_DATA_READY       0   ///< 0 - ������ ������
#define FL_TRIG_READY       1   ///< 1 - ������� ��������������
#define FL_PRED_READY       2   ///< 2 - ��������� ����� �����������
#define FL_POINT_READY      3   ///< 3 - ������� ����, ��� ����� ������ (� ���������� ������)
#define FL_FREQ_READY       4   ///< 4 - ����� ��������� �������
#define FL_PERIOD_READY     5   ///< 5 - ����� ��������� ������
#define FL_LAST_RECOR       6   ///< 6 - ������� ��������� ������ - ����������, ����� ��� ������� ������
#define FL_OVERFLOW_FREQ    8   ///< 8 - ������� ������������ �������� �������
#define FL_OVERFLOW_PERIOD  9   ///< 9 - ������� ������������ �������� �������

#define RD_FLAG_HI          (ADDR_ALTERA + 25)

#define UPR_BIT_PEAKDET            1    ///< ������� �������� - 0/1 ����/���
#define UPR_BIT_CALIBRATOR_AC_DC    2   ///< ����������/����������
#define UPR_BIT_CALIBRATOR_VOLTAGE  3   ///< 0/4�
#define UPR_BIT_RECORDER            4   ///< 0 - ������� �����, 1 - �����������

#define FPGA_MAX_POINTS (8 * 1024)

#define AVE_VALUE           127
#define MIN_VALUE           (AVE_VALUE - 125)
#define MAX_VALUE           (AVE_VALUE + 125)

/// � ����� �������� tBase ������ ���������� ����� ����������� ������
#define MIN_TBASE_P2P       TBase_50ms
/// ����������� ������� �� �������, ��� ������� �������� ��������� ������ �������� ���������
#define MIN_TBASE_PEC_DEAT  TBase_500ns
/// ���� �������� == 0, ������, ��� ���. ��� ����� ��� ������� ������������� � ����������� ������ p2p, � ����� ��� tShift ����� ���������� �������
#define NONE_VALUE  0


/// ����������� �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� �������� 10 ������ ���� �� ����������� �����
#define RShiftMin       20
/// ������� �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� ������������ ������ �� ������ ������
#define RShiftZero      500
/// ������������ �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� �������� 10 ������ ����� �� ����������� �����
#define RShiftMax       980
/// ������� ����� �������� � ����� ������
#define RSHIFT_IN_CELL (((RShiftMax) - (RShiftMin)) / 24)
/// �� ������� ������ ����� �������� �������� ��������, ����� ������ �������� �� ���������� ������������ �� ���� �����.
#define STEP_RSHIFT     (((RShiftMax - RShiftMin) / 24) / 20)


extern uint16 *addressesADC[NumChannels];
#define ADDRESS_READ(ch)    addressesADC[ch];
