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


/// ¬озвращает адрес первой и последней точки на экране в координатах экрана
BitSet64 sDisplay_PointsOnDisplay();
/// \brief ¬озращает адрес первой и последней точки в координатах экрана
BitSet64 sDisplay_BytesOnDisplay();
/// ¬озвращает врем€, через которое меню автоматически скрываетс€, если не было больше нажатий
int sDisplay_TimeMenuAutoHide();
/// ≈сли экран разделЄн на две части и основной сигнал выводитс€ сверху - например, в режиме вывода спектра
bool sDisplay_IsSeparate();
/// brightness = 1..100
void sDisplay_SetBrightness(int16 brightness);

int sDisplay_NumAverage();
/// Ёто смещение экрана по пам€ти в режиме пикового детектора оно будет в два раза меньше, чем байт, потому что кажда€ точка представлена двум€ байтами
int sDisplay_ShiftInMemoryInPoints();

#define SHIFT_IN_MEMORY_IN_POINTS sDisplay_ShiftInMemoryInPoints()

/** @}  @}
 */
