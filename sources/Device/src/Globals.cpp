#include "Globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DAC_HandleTypeDef handleDAC =
{
    DAC
};

HCD_HandleTypeDef handleHCD;


volatile BitField gBF =
{
    0,  // currentNumRAMSignal
    0,  // currentNumROMSignal
    0,  // showHelpHints
    0,  // needFinishDraw
    0,  // showDebugMenu
    0,  // needForSaveToFlashDrive
    0,  // exitFromModeSetNameTo
    0,  // temporaryShowStrNavi
    0,  // runningFPGAbeforeSmallButtons
    0   // exitFromROMtoRAM
};

StateFPGA gStateFPGA =
{
    false,
    StateWorkFPGA_Stop,
    StateCalibration_None
};
