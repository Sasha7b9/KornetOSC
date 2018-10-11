#include "Settings.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum Parameter
{
    DisplayModeDrawSignal = 8,
    DisplayThicknessSignal,
    DisplayBackground,
    DisplayShowStringNavigation,
    DisplayENumMinMax,
    DisplayModeAveraging,
    DisplayENumAverage,
    DisplayENumAccum,
    DisplayModeA
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::TransformForSave(uint8 data[1024])
{
    data[DisplayModeDrawSignal] = set.disp_modeDrawSignal;
    data[DisplayThicknessSignal] = set.disp_thickness;
    data[DisplayBackground] = set.disp_background;
    data[DisplayShowStringNavigation] = set.disp_showStringNavigation;
    data[DisplayENumMinMax] = set.disp_ENumMinMax;
    data[DisplayModeAveraging] = set.disp_modeAveraging;
    data[DisplayENumAverage] = set.disp_ENumAverage;
    data[DisplayENumAccum] = set.disp_ENumAccum;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::TransformFromLoad(uint8 data[1024])
{
}
