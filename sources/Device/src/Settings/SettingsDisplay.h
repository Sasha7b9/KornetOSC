#pragma once
#include "defines.h"
#include "structs.h"
#include "SettingsTime.h"
#include "Display/Display.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsDisplay Settings Display
 *  @{
 */


struct ColorScheme
{
    enum E
    {
        WhiteLetters,   ///< � ���� ������ ��������� ��������� ���� ������� ����� - �� ����� ������ ����� �����
        BlackLetters    ///< � ���� ������ ��������� ��������� ���� ������� ������ - �� ����� ������� ��������
    } value;
};


#define SHIFT_IN_MEMORY             (set.disp_shiftInMemory)
#define TIME_MESSAGES               (set.disp_timeMessages)
#define ENUM_SIGNALS_IN_SEC         (set.disp_ENumSignalsInSec)
#define NUM_SIGNALS_IN_SEC          (sDisplay_NumSignalsInS())
#define LAST_AFFECTED_CH            (set.disp_lastAffectedChannel)
#define LAST_AFFECTED_CH_IS_A       (LAST_AFFECTED_CH.IsA())
#define DISPLAY_ORIENTATION         (set.dbg_Orientation)

#define ALT_MARKERS                 (set.disp_altMarkers)
#define ALT_MARKERS_SHOW            (ALT_MARKERS == AltMarkers::Show)
#define ALT_MARKERS_HIDE            (ALT_MARKERS == AltMarkers::Hide)
#define ALT_MARKERS_AUTO            (ALT_MARKERS == AltMarkers::AutoHide)

#define LINKING_RSHIFT              (set.disp_linkingRShift)

#define MENU_AUTO_HIDE              (set.disp_menuAutoHide)

#define BRIGHTNESS_DISPLAY          (set.disp_brightness)

#define BRIGHTNESS_GRID             (set.disp_brightnessGrid)

#define SET_NUM_BYTES_ON_DISPLAY    (SET_PEAKDET_EN ? 281 * 2 : 281)


/// ���������� ����������� ������� ������
int sDisplay_NumSignalsInS();
/// ������������� ����������� ������� ������
void sDisplay_SetNumSignalsInS(int maxFPS);
/// ���������� ����� ����� ������������� ������� (����� ������� - �����������)
int sDisplay_NumPointSmoothing();
/// ���������� ����� ������ � ��������� ����� �� ������ � ����������� ������
BitSet64 sDisplay_PointsOnDisplay();
/// \brief ��������� ����� ������ � ��������� ����� � ����������� ������
BitSet64 sDisplay_BytesOnDisplay();
/// ���������� �����, ����� ������� ���� ������������� ����������, ���� �� ���� ������ �������
int sDisplay_TimeMenuAutoHide();
/// ���� ����� ������� �� ��� ����� � �������� ������ ��������� ������ - ��������, � ������ ������ �������
bool sDisplay_IsSeparate();
/// brightness = 1..100
void sDisplay_SetBrightness(int16 brightness);

int sDisplay_NumAverage();
/// ��� �������� ������ �� ������ � ������ �������� ��������� ��� ����� � ��� ���� ������, ��� ����, ������ ��� ������ ����� ������������ ����� �������
int sDisplay_ShiftInMemoryInPoints();

#define SHIFT_IN_MEMORY_IN_POINTS sDisplay_ShiftInMemoryInPoints()

/** @}  @}
 */
