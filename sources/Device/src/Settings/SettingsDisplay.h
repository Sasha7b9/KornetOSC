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
