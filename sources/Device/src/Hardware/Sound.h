#pragma once
#include "Settings/Settings.h"
#include "Keyboard/Keyboard.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup Sound
 *  @brief ������ �� �������� ���������
 *  @{
 */


typedef enum
{
    TypeWave_Sine,
    TypeWave_Meandr,
    TypeWave_Triangle
} TypeWave;


class Sound
{
public:
    static void Init();
    /// ���� ������� �� ������.
    static void ButtonPress();
    /// ������� ������� ���� ����������� ������ ������ ���� ����� ���� ������������ ���� ������� ������.
    static void ButtonRelease();

    static void GovernorChangedValue();
    
    static void RegulatorShiftRotate();

    static void RegulatorSwitchRotate();

    static void WarnBeepBad();

    static void WarnBeepGood();
    /// ��� ������� ���� �������� ����� �������/��������� ����. ���� ����������� � ����.
    static void WaitForCompletion();

    static void Beep(TypePress type);

private:

    static void Beep(const TypeWave newTypeWave, const float newFreq, const float newAmpl, const int newDuration);

    static void Stop();

    static void SetWave();

    static void CalculateMeandr();

    static uint16 CalculatePeriodForTIM();

    static void CalculateSine();

    static void CalculateTriangle();

    static void ConfigTIM7(uint16 prescaler, uint16 period);
};


/** @}  @}
 */
