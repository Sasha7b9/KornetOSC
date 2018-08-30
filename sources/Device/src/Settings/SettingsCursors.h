#pragma once
#include "SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

#define CURSORS_SHOW_FREQ           (set.curs_showFreq)

/// ������� ������ ������ ������ �������
#define CURS_SOURCE                 (set.curs_source)
/// ������� ������� ������ A
#define CURS_SOURCE_A               (CURS_SOURCE.IsA())
/// ������� ������� ������ B
#define CURS_SOURCE_B               (CURS_SOURCE.IsB())

/// ���������� �������� ����������, ��������������� 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// ���������� �������� �������, �������������� 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

#define CURS_SHOW                   (set.curs_showCursors)



/// �������� ������ ������� �������
//const char *sCursors_GetCursorTime(Chan source, int numCur, char buffer[20]);
/// �������� ������ ��������� �������� ����������
//const char *sCursors_GetCursorPercentsU(Chan source, char buffer[20]);
/// �������� ������ ��������� �������� �������
//const char *sCursors_GetCursorPercentsT(Chan source, char buffer[20]);

void SetCursPosT_temp(Chan ch, int num, float value);

/** @}  @}
 */
