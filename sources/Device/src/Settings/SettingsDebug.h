#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsDegug Settings Debug
 *  @{
 */

#define CONSOLE_NUM_STRINGS     (set.dbg__numStrings)
#define CONSOLE_SIZE_FONT       (set.dbg__sizeFont ? 8 : 5)
/// Если truе, то включён режим остновки консоли, в котором нажатие ПУСК/СТОП приостанавливает вывод в консоль.
#define MODE_PAUSE_CONSOLE      (set.dbg__modePauseConsole)
#define NUM_MEASURES_FOR_GATES  (set.dbg_NumMeasuresForGates)
#define TIME_COMPENSATION       (set.dbg_TimeCompensation)
#define SHOW_RAND_INFO          (set.dbg_ShowRandInfo)
#define SHOW_RAND_STAT          (set.dbg_ShowRandStat)
#define SHOW_STAT               (set.dbg_ShowStats)
#define PRETRIGGERED            (set.dbg_Pretriggered)
#define BANDWIDTH_DEBUG(ch)     (set.dbg_Bandwidth[ch])

#define DBG_SHOW_ALL            (set.dbg__showAll)
#define DBG_SHOW_FLAG           (set.dbg__showFlag)


float   GetStretchADC(Channel ch);

void    SetStretchADC(Channel ch, float kStretch);

/** @}  @}
 */
