#include "Settings.h"
#include "Tables.h"
#include "Display/Painter.h"
#include "SettingsDisplay.h"
#include "Utils/Math.h"





//---------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_NumAverage()
{
    /*
    if (MODE_EMS && (ENUM_AVE < ENumAverage_8))
    {
        return 8;
    }
    */

    if (!IN_RANDOM_MODE)
    {
        return NUM_AVE;
    }
    else if (NRST_NUM_AVE_FOR_RAND > NUM_AVE)
    {
        return NRST_NUM_AVE_FOR_RAND;
    }

    return NUM_AVE;
}




//----------------------------------------------------------------------------------------------------------------------------------------------------
BitSet64 sDisplay_BytesOnDisplay()
{
    BitSet64 retValue;

    retValue.sword0 = SHIFT_IN_MEMORY;
    retValue.sword1 = retValue.sword0 + (SET_PEAKDET_EN ? 281 * 2 : 281);

    return retValue;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_ShiftInMemoryInPoints()
{
    if (SET_PEAKDET_DIS)
    {
        return SHIFT_IN_MEMORY;
    }
    return SHIFT_IN_MEMORY / 2;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int sDisplay_TimeMenuAutoHide()
{
    static const int times[] =
    {
        0, 5, 10, 15, 30, 60
    };
    return times[MENU_AUTO_HIDE] * 1000;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool sDisplay_IsSeparate()
{
    return FUNC_MODE_DRAW_IS_SEPARATE || FFT_ENABLED;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void sDisplay_SetBrightness(int16 brightness)
{
    BRIGHTNESS_DISPLAY = brightness;
    Painter::SetBrightnessDisplay(brightness);
}
