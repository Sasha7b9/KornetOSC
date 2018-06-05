#pragma once
#include "defines.h"


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
    uint exitFromROMtoRAM               : 1;    ///< Если 1, то выходить из страницы внутренней памяти нужно не стандартно, а в меню последних.
};

extern volatile BitField gBF;   ///< @brief Структура сделана volatile, потому что иначе при вклюённой оптимизации зависает во время выключения. 
                                ///< Вероятно, это связано с переменной soundIsBeep (перед стиранием сектора в цикле происходит ожидание, когда эта 
                                ///< переменная изменит своё состояние (каковое изменение происходит из прерывания, ясен перец)).

enum StateWorkFPGA
{
    StateWorkFPGA_Stop,     ///< СТОП - не занимается считыванием информации.
    StateWorkFPGA_Wait,     ///< Ждёт поступления синхроимпульса.
    StateWorkFPGA_Work,     ///< Идёт работа.
    StateWorkFPGA_Pause     ///< Это состояние, когда временно приостановлен прибор, например, для чтения данных или для записи значений регистров.
};
