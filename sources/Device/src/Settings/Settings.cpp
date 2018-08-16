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

                                            // ���� �������

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
    /* disp_lastAffectedChannel;  */    A,

                                            // ���� ����� 1, ����� 2

    /* chan_shift[NumChannels];  */     { RShiftZero, RShiftZero },
    /* chan_range[NumChannels];  */     { Range::_500mV, Range::_500mV },
    /* chan_couple[NumChannels]; */     { ModeCouple::DC, ModeCouple::DC },
    /* chan_enable[NumChannels]; */     { true, true },
    /* chan_balanceShiftADC[2];  */     { 0, 0 },
    /* chan_bandwidth[2];        */     { Bandwidth::_20MHz, Bandwidth::_20MHz },
    /* chan_resistance[2];       */     { Resistance::_1Mom, Resistance::_1Mom },
    /* chan_inverse[2];          */     { false, false },
    /* chan_divider[2];          */     { Divider::_1, Divider::_1 },
    /* chan_calibrationMode[2];  */     { CalibrationMode::Disable, CalibrationMode::Disable }, 

                                            // ���� �������������

    /* trig_source;             */      TrigSource::A,
    /* trig_input;              */      TrigInput::Full,
    /* trig_polarity;           */      TrigPolarity::Rising,
    /* trig_lev[NumChannels];   */      { TrigLevZero, TrigLevZero },
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
    /* curs_lookMode[2];             */ { CursLookMode::None, CursLookMode::None },
    /* curs_showFreq;                */ true,
    /* curs_active;                  */ CursActive::None,
    /* curs_source;                  */ A,
    /* curs_cntrlU[NumChannels];     */ { CursCntrl::Disable, CursCntrl::Disable },
    /* curs_cntrlT[NumChannels];     */ { CursCntrl::Disable, CursCntrl::Disable },
    /* curs_movement;                */ CursMovement::Pixels,
    /* curs_deltaU100percents[2];    */ { 100, 100 },
    /* curs_deltaT100percents[2];    */ { 100, 100 },
    /* curs_posCurU[NumChannels][2]; */ { { 100, 100 },{ 100, 100 } },
    /* curs_posCurT[NumChannels][2]; */ { { 100, 100 },{ 100, 100 } },

        // ���� ������

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

    // ���� ���������

    /* meas_show;            */ false,
    /* meas_number;          */ MeasuresNumber::_1_5,
    /* meas_source;          */ MeasSource::A_B,
    /* meas_modeViewSignals; */ ModeViewSignals::AsIs,
    /* meas_measures[15];    */ {},
    /* meas_marked;          */ Meas::Freq,

    // ���� ������

    // ��������� ����������

    // ��������� �����������

    // ��������� ������-����������

    // ��������� ����

    // �������������� ��������� ����������

    /*
    RU,                             // serv_lang
    Control_Voltage,                // test_control
    Polarity_Positive,              // test_polarity
    StepU_100mV,                    // test_stepU
    StepI_4mA,                      // test_stepI
    0,                              // test_smooth
    0,                              // menu_currentPage
    false                           // menu_show
    */
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

    return names[range][LANG];
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *NameTBase(TBase tBase)
{
    static const char *names[TBase::Size][Language::Num] =
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
