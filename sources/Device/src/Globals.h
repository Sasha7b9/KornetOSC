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
/// В этом при нажатии на кнопки вместо выполнения её функции выводится информация о её назначении
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
/// Если 1, то консоль находится в режиме паузы
#define CONSOLE_IN_PAUSE        (gBF.consoleInPause)

#define FM_NEED_REDRAW          (gBF.needRedrawFileManager)
#define FM_REDRAW_FULL          1
#define FM_REDRAW_FOLDERS       2
#define FM_REDRAW_FILES         3


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct BitField
{
    int16 currentNumRAMSignal;               ///< Текущий номер последнего сигнала в режиме ПАМЯТЬ - Последние.
    int8 currentNumROMSignal;                ///< Текущий номер сигнала, сохранённого в ППЗУ.
    uint showHelpHints                  : 1; ///< Если 1, то при нажатии кнопки вместо выполнения её фунции выводится подсказка о её назначении.
    uint needFinishDraw                 : 1; ///< Если 1, то нужно немедленно завершить отрисовку и вывести на экран то, что уже нарисовано.
    uint showDebugMenu                  : 1;
    uint needForSaveToFlashDrive        : 1; ///< Если 1, то нужно сохранить после отрисовки на флешку.
    uint exitFromModeSetNameTo          : 2; ///< \brief Куда возвращаться из окна установки имени при сохранении : 0 - в основное меню, 1 - 
                                             ///< в окно последних, 2 - в окно Внутр ЗУ, 3 - в основно окно в выключенным меню.
    uint temporaryShowStrNavi           : 1; ///< Признак того, что нужно временно показывать строку навигации меню.
    uint runningFPGAbeforeSmallButtons  : 1; ///< Здесь сохраняется информация о том, работала ли ПЛИС перед переходом в режим работы с памятью.
    uint exitFromROMtoRAM               : 1; ///< Если 1, то выходить из страницы внутренней памяти нужно не стандартно, а в меню последних.
    uint FPGAneedAutoFind               : 1; ///< Если 1, то нужно найти сигнал.
    uint needRedrawFileManager          : 2; ///< @brief Если 1, то файл-менеджер нуждается в полной перерисовке.
                                             ///< Если 2, то перерисовать только каталоги.
                                             ///< Если 3, то перерисовать только файлы.
    uint alwaysShowROMSignal            : 1; ///< Если 1, то показывать всегда выбранный в режиме "Внутр. ЗУ" сигнал.
    uint panelControlReceive            : 1; ///< Если 1, то панель прислала команду.
    uint FPGAinProcessingOfRead         : 1;
    uint consoleInPause                 : 1; ///< Если 1, то консоль находится в режиме паузы.
};

extern volatile BitField gBF;   ///< @brief Структура сделана volatile, потому что иначе при вклюённой оптимизации зависает во время выключения. 
                                ///< Вероятно, это связано с переменной soundIsBeep (перед стиранием сектора в цикле происходит ожидание, когда эта 
                                ///< переменная изменит своё состояние (каковое изменение происходит из прерывания, ясен перец)).

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
    StateWorkFPGA_Stop,     ///< СТОП - не занимается считыванием информации.
    StateWorkFPGA_Wait,     ///< Ждёт поступления синхроимпульса.
    StateWorkFPGA_Work,     ///< Идёт работа.
    StateWorkFPGA_Pause     ///< Это состояние, когда временно приостановлен прибор, например, для чтения данных или для записи значений регистров.
};

struct StateFPGA
{
    bool needCalibration;                       ///< Установленное в true значение означает, что необходимо произвести калибровку.
    StateWorkFPGA stateWorkBeforeCalibration;
    StateCalibration stateCalibration;          ///< Текущее состояние калибровки. Используется в процессе калибровки.
};


extern StateFPGA gStateFPGA; 
