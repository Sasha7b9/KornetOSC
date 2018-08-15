#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

#define CURSORS_SHOW_FREQ           (set.curs_showFreq)
/// ������������� �������� ��� �������� ����� ��������� - �� ������ ��� ���������
#define CURS_MOVEMENT               (set.curs_movement)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == CursMovement::Percents)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1 �������
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == CursMovement::Pixels)

/// ������� ������ ������ ������ �������
#define CURS_SOURCE                 (set.curs_source)
/// ������� ������� ������ A
#define CURS_SOURCE_A               (CURS_SOURCE == A)
/// ������� ������� ������ B
#define CURS_SOURCE_B               (CURS_SOURCE == B)

#define CURsU_CNTRL_CH(ch)          (set.curs_cntrlU[ch])
#define CURsU_CNTRL                 (CURsU_CNTRL_CH(CURS_SOURCE))
#define CURsU_CNTRL_1               (CURsU_CNTRL == CursCntrl::_1)
#define CURsU_CNTRL_2               (CURsU_CNTRL == CursCntrl::_2)
#define CURsU_CNTRL_1_2             (CURsU_CNTRL == CursCntrl::_1_2)
#define CURsU_DISABLED              (CURsU_CNTRL == CursCntrl::Disable)
#define CURsU_ENABLED               (!CURsU_DISABLED)

#define CURsT_CNTRL_CH(ch)          (set.curs_cntrlT[ch])
#define CURsT_CNTRL                 (CURsT_CNTRL_CH(CURS_SOURCE))
#define CURsT_CNTRL_1               (CURsT_CNTRL == CursCntrl::_1)
#define CURsT_CNTRL_2               (CURsT_CNTRL == CursCntrl::_2)
#define CURsT_CNTRL_1_2             (CURsT_CNTRL == CursCntrl::_1_2)
#define CURsT_DISABLED              (CURsT_CNTRL == CursCntrl::Disable)
#define CURsT_ENABLED               (!CURsT_DISABLED)

/// ������� ������� ����������
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])
/// ������� ������� �������
#define CURsT_POS(ch, num)          GetCursPosT(ch, num)

/// ���������� �������� ����������, ��������������� 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// ���������� �������� �������, �������������� 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

/// ������ ��������� ��������� ����� ���������
#define CURS_ACTIVE                 (set.curs_active)
/// ����� ��������� ��������� ��������� ����������
#define CURS_ACTIVE_U               (CURS_ACTIVE == CursActive::U)
/// ����� ��������� ��������� ��������� �������
#define CURS_ACTIVE_T               (CURS_ACTIVE == CursActive::T)

/// ����� �������� �� ���������
#define CURS_LOOK_MODE(ch)          (set.curs_lookMode[ch])
/// �������� �������� �� ��������� ����������
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Voltage)
/// �������� �������� �� ��������� �������
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Time)
/// �������� �������� �� ��������� ������� � ����������
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == CursLookMode::Both)

#define CURS_SHOW                   (set.curs_showCursors)


 /// �������� ������� ������� ����������
float sCursors_GetCursPosU(Channel ch, int numCur);
/// ���������� true,���� ����� �������� �������
bool  sCursors_NecessaryDrawCursors();
/// �������� ������ ������� ����������
const char *sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20]);
/// �������� ������ ������� �������
const char *sCursors_GetCursorTime(Channel source, int numCur, char buffer[20]);
/// �������� ������ ��������� �������� ����������
const char *sCursors_GetCursorPercentsU(Channel source, char buffer[20]);
/// �������� ������ ��������� �������� �������
const char *sCursors_GetCursorPercentsT(Channel source, char buffer[20]);
/// ���������� �������� ������� �������
float GetCursPosT(Channel ch, int num);

void SetCursPosT_temp(Channel ch, int num, float value);

/** @}  @}
 */
