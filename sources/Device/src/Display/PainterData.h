#pragma once
#include "defines.h"
#include "FPGA/FPGATypes.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PainterData
{
public:
    static void DrawData();
    static void DrawChannel(Channel ch, uint8 data[FPGA_MAX_NUM_POINTS]);
};
