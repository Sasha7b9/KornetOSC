#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

#define CURSORS_SHOW_FREQ           (set.curs_showFreq)
/// Перемемещение курсоров при вращении ручки УСТАНОВКА - по точкам или процентам
#define CURS_MOVEMENT               (set.curs_movement)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == CursMovement::Percents)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1 пиксель
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == CursMovement::Pixels)

/// Курсоры какого канала сейчас активны
#define CURS_SOURCE                 (set.curs_source)
/// Активны курсоры канала A
#define CURS_SOURCE_A               (CURS_SOURCE == A)
/// Активны курсоры канала B
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

/// Позиция курсора напряжения
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])
/// Позиция куросра времени
#define CURsT_POS(ch, num)          GetCursPosT(ch, num)

/// Абсолютное значение напряжения, соответствующее 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// Абсолютное значение времени, соотвествующее 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

/// Какими курсорами управляет ручка УСТАНОВКА
#define CURS_ACTIVE                 (set.curs_active)
/// Ручка УСТАНОВКА управляет курсорами напряжения
#define CURS_ACTIVE_U               (CURS_ACTIVE == CursActive::U)
/// Ручка УСТАНОВКА управляет курсорами времени
#define CURS_ACTIVE_T               (CURS_ACTIVE == CursActive::T)

/// Режим слежения за курсорами
#define CURS_LOOK_MODE(ch)          (set.curs_lookMode[ch])
/// Включено слежение за курсорами напряжения
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Voltage)
/// Включено слежение за курсорами времени
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Time)
/// Включено слежение за курсорами времени и напряжения
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == CursLookMode::Both)

#define CURS_SHOW                   (set.curs_showCursors)


 /// Получить позицию курсора напряжения
float sCursors_GetCursPosU(Channel ch, int numCur);
/// Возвращает true,если нужно рисовать курсоры
bool  sCursors_NecessaryDrawCursors();
/// Получить строку курсора напряжения
const char *sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20]);
/// Получить строку курсора времени
const char *sCursors_GetCursorTime(Channel source, int numCur, char buffer[20]);
/// Получить строку процентов курсоров напряжения
const char *sCursors_GetCursorPercentsU(Channel source, char buffer[20]);
/// Получить строку процентов курсоров времени
const char *sCursors_GetCursorPercentsT(Channel source, char buffer[20]);
/// Возвращает значение курсора времени
float GetCursPosT(Channel ch, int num);

void SetCursPosT_temp(Channel ch, int num, float value);

/** @}  @}
 */
