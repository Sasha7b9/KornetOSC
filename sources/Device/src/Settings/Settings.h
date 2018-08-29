#pragma once
#include "defines.h"
#include "Utils/Measures.h"
#include "Menu/MenuItems.h"
#include "SettingsChannel.h"
#include "SettingsDisplay.h"
#include "SettingsTime.h"
#include "SettingsMath.h"
#include "SettingsMemory.h"
#include "SettingsTrig.h"
#include "SettingsDebug.h"
#include "SettingsNRST.h"
#include "SettingsService.h"
#include "SettingsMeasures.h"
#include "SettingsCursors.h"
#include "SettingsMultimeter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TESTER_NUM_POINTS               (240)

#define SET_SIZE                        (set.size)
#define SET_CRC32                       (set.crc32)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IN_RANDOMIZE_MODE               (SET_TBASE < TBase::_100ns)
#define CURRENT_PAGE                    (set.menu_currentPage)

#define TRIG_MODE                       (set.trig_mode)

#define TESTER_CONTROL                  (set.test_control)
#define TESTER_CONTROL_IS_U             (TESTER_CONTROL == TesterControl::Voltage)
#define TESTER_POLARITY                 (set.test_polarity)
#define TESTER_POLARITY_IS_POSITITVE    (TESTER_POLARITY == TesterPolarity::Positive)
#define TESTER_STEP_U                   (set.test_stepU)
#define TESTER_STEP_I                   (set.test_stepI)
#define TESTER_NUM_SMOOTH               (set.test_smooth)

#define MENU_IS_SHOWN                   (set.menu_show)


/// Возвращает позицию активного пункта на странице namePage.
#define MENU_POS_ACT_ITEM(name)     (set.menu_posActItem[name])
/// Текущая подстраница
#define MENU_CURRENT_SUBPAGE(name)  (set.menu_currentSubPage[name])

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings
{
public:
    static void Load(bool _default = false);
    static void Save();
    static void Reset();
    /// Сбросить цвета на значения по умолчанию
    static void ResetColors();
    /// Возвращает указатель на настройки по умолчанию
    static Settings &GetDefault();

    uint                size;                               ///< Размер данной структуры в байтах
    uint                crc32;                              ///< \brief Контрольная сумма данной структуры с хранящимися в ней настройками

    // Меню ДИСПЛЕЙ
                                                            ///< вычисляется от первого байта, следующего за этим полем
    ModeDrawSignal      disp_modeDrawSignal;
    ThicknessSignal     disp_thickness;                     ///< Толщина линии, которой рисуется сигнал
    Background          disp_background;                    ///< Цвет фона.
    ShowStrNavi         disp_showStringNavigation;          ///< Режим показа строки навигации меню.
    ENumMinMax          disp_ENumMinMax;                    ///< Перечисление количества измерений для определения минимумов и масимумов.
    ModeAveraging       disp_modeAveraging;                 ///< Тип усреднений по измерениям.
    ENumAverage         disp_ENumAverage;                   ///< Число усреднений сигнала.
    ENumAccum           disp_ENumAccum;                     ///< Число накоплений сигнала на экране.
    ModeAccumulation    disp_modeAccumulation;              ///< Режим накопления сигналов.
    ENumSmoothing       disp_ENumSmoothing;                 ///< Перечисление количества точек для скользящего фильтра.
    ENumSignalsInSec    disp_ENumSignalsInSec;              ///< Перечисление числа считываний сигнала в секунда.
    TypeGrid            disp_typeGrid;                      ///< Тип сетки
    int16               disp_brightnessGrid;                ///< Яркость сетки от 0 до 100.
    LinkingRShift       disp_linkingRShift;                 ///< Тип привязки к смещению по вертикали.
    int16               disp_brightness;                    ///< Яркость дисплея.
    int16               disp_timeShowLevels;                ///< Время, в течение которого нужно показывать уровин смещения.
    int16               disp_timeMessages;                  ///< Время в секундах, на которое сообщение остаётся на экрне.
    AltMarkers          disp_altMarkers;                    ///< Режим отображения дополнительных боковых маркеров смещений.
    MenuAutoHide        disp_menuAutoHide;                  ///< Через сколько времени после последнего нажатия клавиши прятать меню.
    int16               disp_shiftInMemory;                 ///< \brief Показывает смещение левого края стеки относительно нулевого байта памяти в 
                                                            ///< байтах. Т.е. для пикового детектора будет в два раза больше количества точек на экране.
    Chan                disp_lastAffectedChannel;           ///< \brief Последний управляемый канал. Используется для правильного вывода сигналов
                                                            ///< на экран с наложением один поверх другого

    // Меню КАНАЛ 1, КАНАЛ 2

    uint16              chan_shift[Chan::Num];              ///< Сдвиг канала по вертикали
    Range               chan_range[Chan::Num];              ///< Масштаб канала по вертикали
    ModeCouple          chan_couple[Chan::Num];             ///< Связь по входу
    bool                chan_enable[Chan::Num];             ///< Включен/выключен канал
    int8                chan_balanceShiftADC[2];            ///< Добавочное смещение для балансировки АЦП.
    Bandwidth           chan_bandwidth[2];                  ///< Ограничение полосы.
    Resistance          chan_resistance[2];                 ///< Сопротивление входа.
    bool                chan_inverse[2];
    Divider             chan_divider[2];                    ///< Множитель.
    CalibrationMode     chan_calibrationMode[2];            ///< Режим калибровки.

    // Меню СИНХРОНИЗАЦИЯ

    TrigSource          trig_source;
    TrigInput           trig_input;
    TrigPolarity        trig_polarity;
    uint16              trig_lev[Chan::Num];
    StartMode           trig_startMode;                     ///< Режим запуска.
    TrigModeFind        trig_modeFind;                      ///< Поиск синхронизации - вручную или автоматически.

    // Меню РАЗВЁРТКА

    int                 time_shift;
    TBase               time_base;
    PeakDetMode         time_peakDet;
    TPos                time_TPos;
    SampleType          time_sampleType;
    FunctionTime        time_timeDivXPos;
    LinkingTShift       time_linkingTShift;                 ///< Тип привязки смещения по горизонтали
    SampleType          time_sampleTypeOld;

    // Меню КУРСОРЫ

    bool                curs_showCursors;                   ///< Показывать ли курсоры.
    CursLookMode        curs_lookMode[2];                   ///< Режимы слежения за курсорами для двух пар курсоров.
    bool                curs_showFreq;                      ///< Установленное в true значение, что нужно показывать на экране 1/dT между курсорами.
    CursActive          curs_active;                        ///< Какие курсоры сейас активны.
    Chan                curs_source;                        ///< Источник - к какому каналу относятся курсоры.
    CursCntrl           curs_cntrlU[Chan::Num];             ///< Активные курсоры напряжения.
    CursCntrl           curs_cntrlT[Chan::Num];             ///< Активные курсоры времени.
    CursMovement        curs_movement;                      ///< Как перемещаться курсорам - по точкам или процентам.
    float               curs_deltaU100percents[2];          ///< Расстояние между курсорами напряжения для 100%, для обоих каналов.
    float               curs_deltaT100percents[2];          ///< Расстояние между курсорами времени для 100%, для обоих каналов.
    float               curs_posCurU[Chan::Num][2];         ///< Текущие позиции курсоров напряжения обоих каналов.
    float               curs_posCurT[Chan::Num][2];         ///< Текущие позиции курсоров времени обоих каналов.

    // Меню ПАМЯТЬ

#define MAX_SYMBOLS_IN_FILE_NAME 35
    ENumPointsFPGA      mem_enumPoints;                             ///< Число точек
    ModeBtnMemory       mem_modeBtnMemory;
    ModeWork            mem_modeWork;                               ///< Режим работы.
    bool                mem_flashAutoConnect;                       ///< Если true, при подключении флешки автоматически выводится Файл-Менеджер.
    int8                mem_indexCurSymbolNameMask;                 ///< Индекс текущего символа в режиме задания маски или выбора имени.
    ModeSaveSignal      mem_modeSaveSignal;                         ///< В каком виде сохранять сигнал.
    char                mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     ///< Имя файла для режима ручного задания.
    ModeShowIntMem      mem_modeShowIntMem;                         ///< Что показывать в режиме ВНУТР ЗУ - считанный или записанный сигнал.
    FileNamingMode      mem_fileNamingMode;                         ///< Режим именования файлов.
    char                mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief Здесь маска для автоматического именования файлов.
                        ///< \details Правила именования.\n
                        /// \code
                        /// %y('\x42') - год, %m('\x43') - месяц, %d('\x44') - день, %H('\x45') - часы, %M('\x46') - минуты, %S('\x47') - секунды
                        /// %Nn('\x48''n') - порядковый номер, котрый занимает не менее n знакомест, например, 7 в %3N будет преобразовано в 007
                        /// Примеры
                        /// name_%4N_%y_%m_%d_%H_%M_%S будет генерировать файлы вида name_0043_2014_04_25_14_45_32
                        /// При этом обратите внимание, что если спецификатор %4N стоИт после временнЫх параметров, то, скорее всего, этот параметр 
                        /// будет всегда равен 0001, т.к. для определения номера просматриваются.
                        /// \endcode

    // Меню ИЗМЕРЕНИЯ

    bool                meas_show;                      ///< Показывать ли измерения.
    MeasuresNumber      meas_number;                    ///< Сколько измерений выводить.
    MeasSource          meas_source;                    ///< Для каких каналов выводить измерения.
    ModeViewSignals     meas_modeViewSignals;           ///< Сжимать ли сигналы при выводе измерений.
    Meas                meas_measures[15];              ///< Выбранные для индикации измерения.
    Meas                meas_marked;                    ///< Измерение, на которое нужно выводить маркеры.

    // Меню СЕРВИС

    Language            serv_lang;
    ColorScheme         serv_colorScheme;
    bool                serv_recorder;                  ///< Включён ли режим регистратора.
    CalibratorMode      serv_calibratorMode;            ///< Режим работы калибратора.
    bool                serv_soundEnable;               ///< Включены ли звуки.
    int16               serv_soundVolume;               ///< Громкость звука [0...100].

    // Настройки математики

    FuncModeDraw        math_modeDraw;                  ///< Раздельный или общий дисплей в режиме математической функции.
    bool                math_enableFFT;
    ScaleFFT            math_scaleFFT;
    SourceFFT           math_sourceFFT;
    WindowFFT           math_windowFFT;
    uint8               math_currentCursor;             ///< Определяет, каким курсором спектра управляет ручка УСТАНОВКА.
    uint8               math_posCur[2];                 ///< Позиция курсора спектра. Изменяется 0...256.
    FFTmaxDB            math_FFTmaxDB;
    Function            math_function;
    ModeRegSet          math_modeRegSet;                ///< Функция ручки УСТАНОВКА - масштаб по времени или смещение по вертикали.
    Range               math_range;
    Divider             math_divider;
    uint16              math_rShift;

    // Настройки частотомера

    bool                freq_enable;
    TimeCounting        freq_timeCounting;              ///< Время счёта частоты.
    FreqClc             freq_freqClc;                   ///< Частота заполнения.
    NumberPeriods       freq_numberPeriods;             ///< Количество периодов.

    // Меню ОТЛАДКА

    int16               dbg_numStrings;                 ///< Число строк в консоли.
    int8                dbg_sizeFont;                   ///< Размер шрифта консоли - 0 - 5, 1 - 8.
    bool                dbg_modePauseConsole;           ///< Если true, то вывод в консоль останавливается нажатием кнопки ПУСК/СТОП.
    bool                dbg_showAll;
    bool                dbg_showFlag;
    bool                dbg_showRShift[2];
    bool                dbg_showTrigLev;
    bool                dbg_showRange[2];
    bool                dbg_showChanParam[2];
    bool                dbg_showTrigParam;
    bool                dbg_showTShift;
    bool                dbg_showTBase;
    int16               dbg_numMeasuresForGates;        ///< Число измерений для ворот.
    bool                dbg_showRandInfo;               ///< Выводить информацию по рандомизатору - ворота и считанное значение.
    bool                dbg_showRandStat;               ///< Выводить график статистики.
    int16               dbg_timeCompensation;           ///< Дополнительное смещение по времени для данной развёртки режима рандомизатора.
    int16               dbg_pretriggered;               ///< Регулируемая величина предзапуска для исследования рандомизатора.
    Bandwidth           dbg_bandwidth[2];               ///< \brief Здесь задаётся полоса, которая будет включаться при выборе в "КАНАЛ-Полоса" 
                                                        ///< значения "Полная".
    bool                dbg_ShowStats;                  ///< Показывать статистику на экране (fps, например).
    DisplayOrientation  dbg_Orientation;

    // Настройки тестер-компонента

    TesterControl       test_control;
    TesterPolarity      test_polarity;
    TesterStepU         test_stepU;
    TesterStepI         test_stepI;
    uint8               test_smooth;                                ///< Количество сглаживаний

    // Настройки меню

    const Page*         menu_currentPage;                           ///< Указатель на открытую страницу меню
    bool                menu_show;                                  ///< Если true, то нужно показывать текущую страницу
    int8                menu_posActItem[Page_NumPages];             ///< \brief Позиция активного пункта. bit7 == 1 - item is opened, 0x7f - нет 
                                                                    ///< активного пункта.
    int8                menu_currentSubPage[Page_NumPages];         ///< Номер текущей подстраницы.

    // Несбрасываемые настройки калибровки

    int16               nrst_balanceADC[Chan::Num];                 ///< Значение дополнительного смещения АЦП для ручной балансировки.
    BalanceADC          nrst_balanceADCtype;                        ///< Тип балансировки.
    StretchADC          nrst_stretchADCtype;                        ///< Тип растяжки канала.
    int16               nrst_StretchADC[Chan::Num][3];              ///< \brief Поправочный коэффициент для ручного, калибровочного и
                        ///< отключенного режимов. Здесь хранится в целом виде, чтобы получить реальный коэффициент, нужно разделить на 1000 и
                        ///< прибавить единицу.
    int16               nrst_rShiftAddStable[Chan::Num][3];         ///< Добавочное смещение для трёх самых чувствительных диапазонов. Задаётся единожды при настройке
    int16               nrst_numAveForRand;                         ///< По скольким измерениям усреднять сигнал в режиме рандомизатора.
    int16               nrst_numSmoothForRand;                      ///< Число точек для скользящего фильта в рандомизаторе.
    int16               nrst_rShiftAdd[Chan::Num][Range::Size][2];  ///< Добавочное смещение, которое пишется сюда при калибровке и балансировке
    int16               nrst_correctionTime;                        ///< Коэффициент коррекции времени.

    // Настройки мультиметра
    MultiAVP        multi_avp;
    MultiMeasures   multi_meas;
    MultiRangeCV    multi_rangeCV;
    MultiRangeVV    multi_rangeVV;
    MultiRangeResistance multi_rangeResist;
};

#pragma pack(pop)

extern Settings set;
