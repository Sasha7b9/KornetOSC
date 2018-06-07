#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern DAC_HandleTypeDef handleDAC;
extern HCD_HandleTypeDef handleHCD;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RETURN_TO_MAIN_MENU     0
#define RETURN_TO_LAST_MEM      1
#define RETURN_TO_INT_MEM       2
#define RETURN_TO_DISABLE_MENU  3


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// � ���� ��� ������� �� ������ ������ ���������� � ������� ��������� ���������� � � ����������
#define HINT_MODE_ENABLED       (gBF.showHelpHints)
#define NEED_FINISH_DRAW        (gBF.needFinishDraw)
#define SHOW_DEBUG_MENU         (gBF.showDebugMenu)
#define NEED_SAVE_TO_FLASHDRIVE (gBF.needForSaveToFlashDrive)
#define EXIT_FROM_SETNAME_TO    (gBF.exitFromModeSetNameTo)
#define SHOW_STRING_NAVIGATION  (gBF.temporaryShowStrNavi)
#define NUM_ROM_SIGNAL          (gBF.currentNumROMSignal)
#define RUN_FPGA_BEFORE_SB      (gBF.runningFPGAbeforeSmallButtons)
#define NUM_RAM_SIGNAL          (gBF.currentNumRAMSignal)
#define EXIT_FROM_ROM_TO_RAM    (gBF.exitFromROMtoRAM)
#define FPGA_NEED_AUTO_FIND     (gBF.FPGAneedAutoFind)
#define ALWAYS_SHOW_ROM_SIGNAL  (gBF.alwaysShowROMSignal)
#define PANEL_CONTROL_RECEIVE   (gBF.panelControlReceive)
#define FPGA_IN_PROCESS_OF_READ (gBF.FPGAinProcessingOfRead)
/// ���� 1, �� ������� ��������� � ������ �����
#define CONSOLE_IN_PAUSE        (gBF.consoleInPause)

#define FM_NEED_REDRAW          (gBF.needRedrawFileManager)
#define FM_REDRAW_FULL          1
#define FM_REDRAW_FOLDERS       2
#define FM_REDRAW_FILES         3


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct BitField
{
    int16 currentNumRAMSignal;               ///< ������� ����� ���������� ������� � ������ ������ - ���������.
    int8 currentNumROMSignal;                ///< ������� ����� �������, ����������� � ����.
    uint showHelpHints                  : 1; ///< ���� 1, �� ��� ������� ������ ������ ���������� � ������ ��������� ��������� � � ����������.
    uint needFinishDraw                 : 1; ///< ���� 1, �� ����� ���������� ��������� ��������� � ������� �� ����� ��, ��� ��� ����������.
    uint showDebugMenu                  : 1;
    uint needForSaveToFlashDrive        : 1; ///< ���� 1, �� ����� ��������� ����� ��������� �� ������.
    uint exitFromModeSetNameTo          : 2; ///< \brief ���� ������������ �� ���� ��������� ����� ��� ���������� : 0 - � �������� ����, 1 - 
                                             ///< � ���� ���������, 2 - � ���� ����� ��, 3 - � ������� ���� � ����������� ����.
    uint temporaryShowStrNavi           : 1; ///< ������� ����, ��� ����� �������� ���������� ������ ��������� ����.
    uint runningFPGAbeforeSmallButtons  : 1; ///< ����� ����������� ���������� � ���, �������� �� ���� ����� ��������� � ����� ������ � �������.
    uint exitFromROMtoRAM               : 1; ///< ���� 1, �� �������� �� �������� ���������� ������ ����� �� ����������, � � ���� ���������.
    uint FPGAneedAutoFind               : 1; ///< ���� 1, �� ����� ����� ������.
    uint needRedrawFileManager          : 2; ///< @brief ���� 1, �� ����-�������� ��������� � ������ �����������.
                                             ///< ���� 2, �� ������������ ������ ��������.
                                             ///< ���� 3, �� ������������ ������ �����.
    uint alwaysShowROMSignal            : 1; ///< ���� 1, �� ���������� ������ ��������� � ������ "�����. ��" ������.
    uint panelControlReceive            : 1; ///< ���� 1, �� ������ �������� �������.
    uint FPGAinProcessingOfRead         : 1;
    uint consoleInPause                 : 1; ///< ���� 1, �� ������� ��������� � ������ �����.
};

extern volatile BitField gBF;   ///< @brief ��������� ������� volatile, ������ ��� ����� ��� ��������� ����������� �������� �� ����� ����������. 
                                ///< ��������, ��� ������� � ���������� soundIsBeep (����� ��������� ������� � ����� ���������� ��������, ����� ��� 
                                ///< ���������� ������� ��� ��������� (������� ��������� ���������� �� ����������, ���� �����)).

enum StateCalibration
{
    StateCalibration_None,
    StateCalibration_ADCinProgress,
    StateCalibration_RShiftAstart,
    StateCalibration_RShiftAinProgress,
    StateCalibration_RShiftBstart,
    StateCalibration_RShiftBinProgress,
    StateCalibration_ErrorCalibrationA,
    StateCalibration_ErrorCalibrationB
};

enum StateWorkFPGA
{
    StateWorkFPGA_Stop,     ///< ���� - �� ���������� ����������� ����������.
    StateWorkFPGA_Wait,     ///< ��� ����������� ��������������.
    StateWorkFPGA_Work,     ///< ��� ������.
    StateWorkFPGA_Pause     ///< ��� ���������, ����� �������� ������������� ������, ��������, ��� ������ ������ ��� ��� ������ �������� ���������.
};

struct StateFPGA
{
    bool needCalibration;                       ///< ������������� � true �������� ��������, ��� ���������� ���������� ����������.
    StateWorkFPGA stateWorkBeforeCalibration;
    StateCalibration stateCalibration;          ///< ������� ��������� ����������. ������������ � �������� ����������.
};


extern StateFPGA gStateFPGA; 
