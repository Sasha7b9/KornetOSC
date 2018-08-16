#include "Settings.h"
#include "FPGA/FPGA.h"
#include "Hardware/EEPROM.h"
#include "Hardware/AT25160N.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Settings defaultSettings =
{
    /* size                       */    0,
    /* crc32                      */    0,

                                            // Меню ДИСПЛЕЙ

    /* disp_modeDrawSignal;       */    ModeDrawSignal::Lines,
    /* disp_thickness;            */    ThicknessSignal::_1,
    /* disp_background;           */    Background::Black,
    /* disp_showStringNavigation; */    ShowStrNavi::Temp,
    /* disp_ENumMinMax;           */    ENumMinMax::_1,
    /* disp_modeAveraging;        */    ModeAveraging::Accurately,
    /* disp_ENumAverage;          */    ENumAverage::_1,
    /* disp_ENumAccum;            */    ENumAccum::_1,
    /* disp_modeAccumulation;     */    ModeAccumulation::NoReset,
    /* disp_ENumSmoothing;        */    ENumSmoothing::Disable,
    /* disp_ENumSignalsInSec;     */    ENumSignalsInSec::_25,
    /* disp_typeGrid;             */    TypeGrid::_1,
    /* disp_brightnessGrid;       */    50,
    /* disp_linkingRShift;        */    LinkingRShift::Position,
    /* disp_brightness;           */    100,
    /* disp_timeShowLevels;       */    5,
    /* disp_timeMessages;         */    5,
    /* disp_altMarkers;           */    AltMarkers::AutoHide,
    /* disp_menuAutoHide;         */    MenuAutoHide::None,
    /* disp_shiftInMemory;        */    0,
    /* disp_lastAffectedChannel;  */    Chan::A,

                                            // Меню КАНАЛ 1, КАНАЛ 2
    
    /* chan_shift[Chan::Num];  */     {RShiftZero, RShiftZero},
    /* chan_range[Chan::Num];  */     {Range::_500mV, Range::_500mV},
    /* chan_couple[Chan::Num]; */     {ModeCouple::DC, ModeCouple::DC},
    /* chan_enable[Chan::Num]; */     {true, true},
    /* chan_balanceShiftADC[2];  */     {0, 0},
    /* chan_bandwidth[2];        */     {Bandwidth::_20MHz, Bandwidth::_20MHz},
    /* chan_resistance[2];       */     {Resistance::_1Mom, Resistance::_1Mom},
    /* chan_inverse[2];          */     {false, false},
    /* chan_divider[2];          */     {Divider::_1, Divider::_1},
    /* chan_calibrationMode[2];  */     {CalibrationMode::Disable, CalibrationMode::Disable},
    
                                            // Меню СИНХРОНИЗАЦИЯ
    
    /* trig_source;             */      TrigSource::A,
    /* trig_input;              */      TrigInput::Full,
    /* trig_polarity;           */      TrigPolarity::Rising,
    /* trig_lev[Chan::Num];   */      {TrigLevZero, TrigLevZero},
    /* trig_startMode;          */      StartMode::Auto,
    /* trig_modeFind;           */      TrigModeFind::Hand,
    
                                            // Меню РАЗВЁРТКА
    
    /* time_shift;          */          0,
    /* time_base;           */          TBase::_500us,
    /* time_peakDet;        */          PeakDetMode::Disabled,
    /* time_TPos;           */          TPos::Center,
    /* time_sampleType;     */          SampleType::Real,
    /* time_timeDivXPos;    */          FunctionTime::Time,
    /* time_linkingTShift;  */          LinkingTShift::Time,
    /* time_sampleTypeOld;  */          SampleType::Real,

                                            // Меню КУРСОРЫ
    
    /* curs_showCursors;             */ false,
    /* curs_lookMode[2];             */ {CursLookMode::None, CursLookMode::None},
    /* curs_showFreq;                */ true,
    /* curs_active;                  */ CursActive::None,
    /* curs_source;                  */ Chan::A,
    /* curs_cntrlU[Chan::Num];     */ {CursCntrl::Disable, CursCntrl::Disable},
    /* curs_cntrlT[Chan::Num];     */ {CursCntrl::Disable, CursCntrl::Disable},
    /* curs_movement;                */ CursMovement::Pixels,
    /* curs_deltaU100percents[2];    */ {100, 100},
    /* curs_deltaT100percents[2];    */ {100, 100},
    /* curs_posCurU[Chan::Num][2]; */ {{ 100, 100 },{ 100, 100 }},
    /* curs_posCurT[Chan::Num][2]; */ {{ 100, 100 },{ 100, 100 }},
    
                                            // Меню ПАМЯТЬ
    
    /* mem_enumPoints;                             */   ENumPointsFPGA::_512,
    /* mem_modeBtnMemory;                          */   ModeBtnMemory::Menu,
    /* mem_modeWork;                               */   ModeWork::Dir,
    /* mem_flashAutoConnect;                       */   false,
    /* mem_indexCurSymbolNameMask;                 */   0,
    /* mem_modeSaveSignal;                         */   ModeSaveSignal::BMP,
    /* mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     */   {},
    /* mem_modeShowIntMem;                         */   ModeShowIntMem::Saved,
    /* mem_fileNamingMode;                         */   FileNamingMode::Mask,
    /* mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; */   {},
    
                                            // Меню ИЗМЕРЕНИЯ
    
    /* meas_show;            */         false,
    /* meas_number;          */         MeasuresNumber::_1_5,
    /* meas_source;          */         MeasSource::A_B,
    /* meas_modeViewSignals; */         ModeViewSignals::AsIs,
    /* meas_measures[15];    */         {},
    /* meas_marked;          */         Meas::Freq,
    
                                            // Меню СЕРВИС
    
    /* serv_lang;           */          Language::RU,
    /* serv_colorScheme;    */          ColorScheme::WhiteLetters,
    /* serv_recorder;       */          false,
    /* serv_calibratorMode; */          CalibratorMode::Freq,
    /* serv_soundEnable;    */          true,
    /* serv_soundVolume;    */          100,

                                            // Настройки математики

    /* math_modeDraw;      */           FuncModeDraw::Disable,
    /* math_enableFFT;     */           false,
    /* math_scaleFFT;      */           ScaleFFT::Log,
    /* math_sourceFFT;     */           SourceFFT::Both,
    /* math_windowFFT;     */           WindowFFT::Hamming,
    /* math_currentCursor; */           0,
    /* math_posCur[2];     */           { 50, 50 },
    /* math_FFTmaxDB;      */           FFTmaxDB::_60,
    /* math_function;      */           Function::Sum,
    /* math_modeRegSet;    */           ModeRegSet::Range,
    /* math_range;         */           Range::_1V,
    /* math_divider;       */           Divider::_1,
    /* math_rShift;        */           RShiftZero,

                                            // Настройки частотомера

    /* freq_enable;        */           false,
    /* freq_timeCounting;  */           TimeCounting::_1s,
    /* freq_freqClc;       */           FreqClc::_1MHz,
    /* freq_numberPeriods; */           NumberPeriods::_10,

                                            // Меню ОТЛАДКА

    /* dbg_numStrings;          */      30,
    /* dbg_sizeFont;            */      8,
    /* dbg_modePauseConsole;    */      false,
    /* dbg_showAll;             */      false,
    /* dbg_showFlag;            */      false,
    /* dbg_showRShift[2];       */      { false, false },
    /* dbg_showTrigLev;         */      false,
    /* dbg_showRange[2];        */      { false, false },
    /* dbg_showChanParam[2];    */      { false, false },
    /* dbg_showTrigParam;       */      false,
    /* dbg_showTShift;          */      false,
    /* dbg_showTBase;           */      false,
    /* dbg_numMeasuresForGates; */      10,
    /* dbg_showRandInfo;        */      false,
    /* dbg_showRandStat;        */      false,
    /* dbg_timeCompensation;    */      0,
    /* dbg_pretriggered;        */      0,
    /* dbg_bandwidth[2];        */      {Bandwidth::_100MHz, Bandwidth::_100MHz},
    /* dbg_ShowStats;           */      false,
    /* dbg_Orientation;         */      DisplayOrientation::Direct,

                                            // Настройки тестер-компонента

    /* test_control;  */                TesterControl::Voltage,
    /* test_polarity; */                TesterPolarity::Positive,
    /* test_stepU;    */                TesterStepU::_100mV,
    /* test_stepI;    */                TesterStepI::_4mA,
    /* test_smooth;   */                0,

                                            // Настройки меню

    /* menu_currentPage;                   */ 0,
    /* menu_show;                          */ false,
    /* menu_posActItem[Page_NumPages];     */ {},
    /* menu_currentSubPage[Page_NumPages]; */ {},

                                            // Несбрасываемые настройки калибровки

    /* nrst_balanceADC[Chan::Num];                */ {},
    /* nrst_balanceADCtype;                         */ BalanceADC::Disable,
    /* nrst_stretchADCtype;                         */ StretchADC::Disable,
    /* nrst_StretchADC[Chan::Num][3];             */ {},
    /* nrst_rShiftAddStable[Chan::Num][3];        */ {},
    /* nrst_numAveForRand;                          */ 0,
    /* nrst_numSmoothForRand;                       */ 0,
    /* nrst_rShiftAdd[Chan::Num][Range::Size][2]; */ {},
    /* nrst_correctionTime;                         */ 0
};

Settings set;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::Load(bool)
{
    Reset();
    //EEPROM::LoadSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Save()
{
    //EEPROM::SaveSettings();

    //AT25160N::Save(set);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Reset()
{
    set = defaultSettings;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameRange(Range range)
{
    static const char *names[Range::Size][Language::Num] =
    {
        {"2мВ",     "2mV"},
        {"5мВ",     "5mV"},
        {"10мВ",    "10mV"},
        {"20мВ",    "20mV"},
        {"50мВ",    "50mV"},
        {"0.1В",    "0.1V"},
        {"0.2В",    "0.2V"},
        {"0.5В",    "0.5V"},
        {"1В",      "1V"},
        {"2В",      "2V"},
        {"5В",      "5V"},
        {"10В",     "10V"},
        {"20В",     "20V"}
    };

    return names[range][LANG];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameTBase(TBase tBase)
{
    static const char *names[TBase::Size][Language::Num] =
    {
        {"2нс",     "2ns"},
        {"5нс",     "5ns"},
        {"10нс",    "10ns"},
        {"20нс",    "20ns"},
        {"50нс",    "50ns"},
        {"0.1мкс",  "0.1us"},
        {"0.2мкс",  "0.2us"},
        {"0.5мкс",  "0.5us"},
        {"1мкс",    "1us"},
        {"2мкс",    "2us"},
        {"5мкс",    "5us"},
        {"10мкс",   "10us"},
        {"20мкс",   "20us"},
        {"50мкс",   "50us"},
        {"0.1мс",   "0.1ms"},
        {"0.2мс",   "0.2ms"},
        {"0.5мс",   "0.5ms"},
        {"1мс",     "1ms"},
        {"2мс",     "2ms"},
        {"5мс",     "5ms"},
        {"10мс",    "10ms"},
        {"20мс",    "20ms"},
        {"50мс",    "50ms"},
        {"0.1с",    "0.1s"},
        {"0.2с",    "0.2s"},
        {"0.5с",    "0.5s"},
        {"1с",      "1s"},
        {"2с",      "2s"},
        {"5с",      "5s"},
        {"10с",     "10s"}
    };

    return names[tBase][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float MaxDBforFFT(FFTmaxDB maxDB)
{
    static const float arrayMAX_DB_FOR_FFT[] = {-40.0f, -60.0f, -80.0f};

    return arrayMAX_DB_FOR_FFT[maxDB];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::ResetColors()
{
}
