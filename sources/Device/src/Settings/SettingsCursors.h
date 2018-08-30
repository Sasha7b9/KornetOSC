#pragma once
#include "SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

#define CURSORS_SHOW_FREQ           (set.curs_showFreq)

/// Курсоры какого канала сейчас активны
#define CURS_SOURCE                 (set.curs_source)
/// Активны курсоры канала A
#define CURS_SOURCE_A               (CURS_SOURCE.IsA())
/// Активны курсоры канала B
#define CURS_SOURCE_B               (CURS_SOURCE.IsB())

/// Абсолютное значение напряжения, соответствующее 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// Абсолютное значение времени, соотвествующее 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

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
