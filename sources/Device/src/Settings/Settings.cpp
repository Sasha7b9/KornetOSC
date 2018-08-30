#include "Settings/Settings.h"
#include "FPGA/FPGA.h"
#include "FPGA/RShift.h"
#include "Hardware/EEPROM.h"
#include "Hardware/AT25160N.h"
#include "Hardware/Hardware.h"
#include "Display/Colors.h"
#include "Menu/Menu.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Settings defaultSettings =
{
    /* size                       */    0,
    /* crc32                      */    0,

                                            // ���� �������

    /* disp_modeDrawSignal;       */    ModeDrawSignal::Lines,
    /* disp_thickness;            */    ThicknessSignal::_1,
    /* disp_background;           */    Display::Background::Black,
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
    /* disp_shiftInMemory;        */    370,                       // ��� ������������� 
    /* disp_lastAffectedChannel;  */    Chan::A,

                                            // ���� ����� 1, ����� 2
    
    /* chan_shift[Chan::Num];    */     {RShift::ZERO, RShift::ZERO},
    /* chan_range[Chan::Num];    */     {Range::_500mV, Range::_500mV},
    /* chan_couple[Chan::Num];   */     {ModeCouple::DC, ModeCouple::DC},
    /* chan_enable[Chan::Num];   */     {true, true},
    /* chan_balanceShiftADC[2];  */     {0, 0},
    /* chan_bandwidth[2];        */     {Bandwidth::Full, Bandwidth::Full},
    /* chan_resistance[2];       */     {Resistance::_1Mom, Resistance::_1Mom},
    /* chan_inverse[2];          */     {false, false},
    /* chan_divider[2];          */     {Divider::_1, Divider::_1},
    /* chan_calibrationMode[2];  */     {CalibrationMode::Disable, CalibrationMode::Disable},
    
                                            // ���� �������������
    
    /* trig_source;             */      TrigSource::A,
    /* trig_input;              */      TrigInput::Full,
    /* trig_polarity;           */      TrigPolarity::Rising,
    /* trig_lev[Chan::Num];     */      {TrigLev::ZERO, TrigLev::ZERO},
    /* trig_startMode;          */      StartMode::Auto,
    /* trig_modeFind;           */      TrigModeFind::Hand,
    
                                            // ���� ���¨����
    
    /* time_shift;          */          0,
    /* time_base;           */          TBase::_500us,
    /* time_peakDet;        */          PeakDetMode::Disabled,
    /* time_TPos;           */          TPos::Center,
    /* time_sampleType;     */          SampleType::Real,
    /* time_timeDivXPos;    */          FunctionTime::Time,
    /* time_linkingTShift;  */          LinkingTShift::Time,
    /* time_sampleTypeOld;  */          SampleType::Real,

                                            // ���� �������
    
    /* curs_showCursors;             */ false,
    /* curs_lookMode[2];             */ {CursLookMode::None, CursLookMode::None},
    /* curs_showFreq;                */ true,
    /* curs_active;                  */ Cursors::Active::None,
    /* curs_source;                  */ Chan::A,
    /* curs_cntrlU[Chan::Num];       */ {CursCntrl::Disable, CursCntrl::Disable},
    /* curs_cntrlT[Chan::Num];       */ {CursCntrl::Disable, CursCntrl::Disable},
    /* curs_movement;                */ Cursors::Movement::Pixels,
    /* curs_deltaU100percents[2];    */ {100, 100},
    /* curs_deltaT100percents[2];    */ {100, 100},
    /* curs_posCurU[Chan::Num][2];   */ {{ 100, 100 },{ 100, 100 }},
    /* curs_posCurT[Chan::Num][2];   */ {{ 100, 100 },{ 100, 100 }},
    
                                            // ���� ������
    
    /* mem_enumPoints;                             */   ENumPointsFPGA::_1k,
    /* mem_modeBtnMemory;                          */   ModeBtnMemory::Menu,
    /* mem_modeWork;                               */   ModeWork::Dir,
    /* mem_flashAutoConnect;                       */   false,
    /* mem_indexCurSymbolNameMask;                 */   0,
    /* mem_modeSaveSignal;                         */   ModeSaveSignal::BMP,
    /* mem_fileName[MAX_SYMBOLS_IN_FILE_NAME];     */   {},
    /* mem_modeShowIntMem;                         */   ModeShowIntMem::Saved,
    /* mem_fileNamingMode;                         */   FileNamingMode::Mask,
    /* mem_fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; */   {},
    
                                            // ���� ���������
    
    /* meas_show;            */         false,
    /* meas_number;          */         MeasuresNumber::_1_5,
    /* meas_source;          */         MeasSource::A_B,
    /* meas_modeViewSignals; */         ModeViewSignals::AsIs,
    /* meas_measures[15];    */         {},
    /* meas_marked;          */         Meas::Freq,
    
                                            // ���� ������
    
    /* serv_lang;           */          Language::RU,
    /* serv_colorScheme;    */          ColorScheme::WhiteLetters,
    /* serv_recorder;       */          false,
    /* serv_calibratorMode; */          CalibratorMode::Freq,
    /* serv_soundEnable;    */          true,
    /* serv_soundVolume;    */          100,

                                            // ��������� ����������

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
    /* math_rShift;        */           RShift::ZERO,

                                            // ��������� �����������

    /* freq_enable;        */           FPGA::FreqMeter::Enabled::Off,
    /* freq_timeCounting;  */           FPGA::FreqMeter::TimeCounting::_1s,
    /* freq_freqClc;       */           FPGA::FreqMeter::FreqClc::_1MHz,
    /* freq_numberPeriods; */           FPGA::FreqMeter::NumberPeriods::_10,

                                            // ���� �������

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
    /* dbg_bandwidth[2];        */      {Bandwidth::Full, Bandwidth::Full},
    /* dbg_ShowStats;           */      false,
    /* dbg_Orientation;         */      DisplayOrientation::Direct,

                                            // ��������� ������-����������

    /* test_control;  */                Tester::Control::Voltage,
    /* test_polarity; */                Tester::Polarity::Positive,
    /* test_stepU;    */                Tester::StepU::_100mV,
    /* test_stepI;    */                Tester::StepI::_4mA,
    /* test_smooth;   */                0,

                                            // ��������� ����

    /* menu_currentPage;                   */ 0,
    /* menu_show;                          */ false,
    /* menu_posActItem[Page_NumPages];     */ {},
    /* menu_currentSubPage[Page_NumPages]; */ {},

                                            // �������������� ��������� ����������

    /* nrst_balanceADC[Chan::Num];                */ {},
    /* nrst_balanceADCtype;                       */ BalanceADC::Disable,
    /* nrst_stretchADCtype;                       */ StretchADC::Disable,
    /* nrst_StretchADC[Chan::Num][3];             */ {},
    /* nrst_rShiftAddStable[Chan::Num][3];        */ {},
    /* nrst_numAveForRand;                        */ 0,
    /* nrst_numSmoothForRand;                     */ 0,
    /* nrst_rShiftAdd[Chan::Num][Range::Size][2]; */ {},
    /* nrst_correctionTime;                       */ 0,

                                // ��������� �����������
    /* multi_avp */         MultiAVP::Off,
    /* multi_meas */        MultiMeasures::VariableVoltage,
    /* multi_rangeCV */     MultiRangeCV::_2V,
    /* multi_rangeVV */     MultiRangeVV::_2V
};

Settings set = defaultSettings;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::Load(bool _default)
{
    if(_default || !EEPROM::LoadSettings())
    {
        Reset();
        FPGA::LoadSettings();
        Menu::Init();
        FPGA::OnPressStart();
    }

    /*
    uint size = 0;
    AT25160N::ReadData(0, (uint8 *)&size, 4);

    if(size > 0 && size < 1024)
    {
        uint8 *data = (uint8 *)malloc(size);

        AT25160N::ReadData(0, data, size);

        uint crc32 = Hardware::CalculateCRC32((uint)data + 8, size - 8);

        if(crc32 == *((uint *)(data + 4)))
        {
            memcpy(&set, data, size);
        }
        else
        {
            Reset();
        }

        free(data);
    }
    else
    {
        Reset();
    }
    */
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Save()
{
    EEPROM::SaveSettings();

    /*
    SET_SIZE = sizeof(Settings);
    SET_CRC32 = Hardware::CalculateCRC32((uint)((uint8 *)&set + 8), SET_SIZE - 8);

    AT25160N::WriteData(0, (uint8 *)&set, SET_SIZE);
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Reset()
{
    set = defaultSettings;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Range::Name() const
{
    static pString names[Range::Size][Language::Num] =
    {
        {"2��",     "2mV"},
        {"5��",     "5mV"},
        {"10��",    "10mV"},
        {"20��",    "20mV"},
        {"50��",    "50mV"},
        {"0.1�",    "0.1V"},
        {"0.2�",    "0.2V"},
        {"0.5�",    "0.5V"},
        {"1�",      "1V"},
        {"2�",      "2V"},
        {"5�",      "5V"},
        {"10�",     "10V"},
        {"20�",     "20V"}
    };

    return names[value][LANG];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString TBase::Name() const
{
    static pString names[TBase::Size][Language::Num] =
    {
        {"2��",     "2ns"},
        {"5��",     "5ns"},
        {"10��",    "10ns"},
        {"20��",    "20ns"},
        {"50��",    "50ns"},
        {"0.1���",  "0.1us"},
        {"0.2���",  "0.2us"},
        {"0.5���",  "0.5us"},
        {"1���",    "1us"},
        {"2���",    "2us"},
        {"5���",    "5us"},
        {"10���",   "10us"},
        {"20���",   "20us"},
        {"50���",   "50us"},
        {"0.1��",   "0.1ms"},
        {"0.2��",   "0.2ms"},
        {"0.5��",   "0.5ms"},
        {"1��",     "1ms"},
        {"2��",     "2ms"},
        {"5��",     "5ms"},
        {"10��",    "10ms"},
        {"20��",    "20ms"},
        {"50��",    "50ms"},
        {"0.1�",    "0.1s"},
        {"0.2�",    "0.2s"},
        {"0.5�",    "0.5s"},
        {"1�",      "1s"},
        {"2�",      "2s"},
        {"5�",      "5s"},
        {"10�",     "10s"}
    };

    return names[value][LANG];
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
Settings &Settings::GetDefault()
{
    return (Settings &)defaultSettings;
}
