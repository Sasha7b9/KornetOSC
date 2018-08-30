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


/// Возвращает число точек сглаживающего фильтра (режим ДИСПЛЕЙ - Сглаживание)
int sDisplay_NumPointSmoothing();
/// Возвращает адрес первой и последней точки на экране в координатах экрана
BitSet64 sDisplay_PointsOnDisplay();
/// \brief Возращает адрес первой и последней точки в координатах экрана
BitSet64 sDisplay_BytesOnDisplay();
/// Возвращает время, через которое меню автоматически скрывается, если не было больше нажатий
int sDisplay_TimeMenuAutoHide();
/// Если экран разделён на две части и основной сигнал выводится сверху - например, в режиме вывода спектра
bool sDisplay_IsSeparate();
/// brightness = 1..100
void sDisplay_SetBrightness(int16 brightness);

int sDisplay_NumAverage();
/// Это смещение экрана по памяти в режиме пикового детектора оно будет в два раза меньше, чем байт, потому что каждая точка представлена двумя байтами
int sDisplay_ShiftInMemoryInPoints();

#define SHIFT_IN_MEMORY_IN_POINTS sDisplay_ShiftInMemoryInPoints()

/** @}  @}
 */
