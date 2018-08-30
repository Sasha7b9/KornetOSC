#pragma once
#include "SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

 /// Режим слежения курсоров.
struct CursLookMode
{
    enum E
    {
        None,      ///< Курсоры не следят.
        Voltage,   ///< Курсоры следят за напряжением автоматически.
        Time,      ///< Курсоры следят за временем автоматически.
        Both       ///< Курсоры следят за временем и напряжением, в зависимости от того, какой курсоры вращали последним.
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Каким курсором управлять
struct CursCntrl
{
    enum E
    {
        _1,        ///< первым
        _2,        ///< вторым
        _1_2,      ///< обоими
        Disable    ///< никаким
    } value;
    operator uint8() const { return (uint8)value; };
};


#define CURSORS_SHOW_FREQ           (set.curs_showFreq)

/// Курсоры какого канала сейчас активны
#define CURS_SOURCE                 (set.curs_source)
/// Активны курсоры канала A
#define CURS_SOURCE_A               (CURS_SOURCE.IsA())
/// Активны курсоры канала B
#define CURS_SOURCE_B               (CURS_SOURCE.IsB())

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

/// Абсолютное значение напряжения, соответствующее 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// Абсолютное значение времени, соотвествующее 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

/// Режим слежения за курсорами
#define CURS_LOOK_MODE(ch)          (set.curs_lookMode[ch])
/// Включено слежение за курсорами напряжения
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Voltage)
/// Включено слежение за курсорами времени
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Time)
/// Включено слежение за курсорами времени и напряжения
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == CursLookMode::Both)

#define CURS_SHOW                   (set.curs_showCursors)



/// Получить строку курсора времени
//const char *sCursors_GetCursorTime(Chan source, int numCur, char buffer[20]);
/// Получить строку процентов курсоров напряжения
//const char *sCursors_GetCursorPercentsU(Chan source, char buffer[20]);
/// Получить строку процентов курсоров времени
//const char *sCursors_GetCursorPercentsT(Chan source, char buffer[20]);

void SetCursPosT_temp(Chan ch, int num, float value);

/** @}  @}
 */
