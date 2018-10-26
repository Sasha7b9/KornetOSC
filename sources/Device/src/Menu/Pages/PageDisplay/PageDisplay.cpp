#include "defines.h"
#include "Display/Painter.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "FPGA/FPGA.h"
#include "Menu/Menu.h"
#include "Utils/CommonFunctions.h"
#include "Utils/Dictionary.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase ppDisplaySettings;
extern const PageBase pageDisplay;

const PageBase *PageDisplay::pointer = &pageDisplay;
const PageBase *PageDisplay::PageSettings::pointer = &ppDisplaySettings;


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cThickness,                                                                                            //--- ������� - ������� ---
             "�������", "Thickness",
             "��������� �������� ������� ��������� �� ����� �����������",
             "Allows you to change the thickness of the signals displayed on the screen",
             "x1", "x1",
             "x3", "x3",
             THICKNESS_SIGNAL, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageDisplay::Init()
{
    PageSettings::PageColors::OnChanged_Settings_Colors_Background(true);   // ������� �������� � �������� ������
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(       cViewMode,                                                                                         //--- ������� - ����������� ---
    "�������.", "View",
    "����� ����� ����������� �������.",
    "Sets the display mode signal.",
    "������", "Vector",
    "�����",  "Points",
    MODE_DRAW_SIGNAL, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_MinMax()
{
    return !IN_RANDOM_MODE && !IN_P2P_MODE;
}

static void OnChanged_MinMax(bool)
{
    /*
    int maxMeasures = DS_NumberAvailableEntries();  
    int numMinMax = sDisplay_NumberMinMax();

    if (maxMeasures < numMinMax)
    {
    display.ShowWarningWithNumber(ExcessValues, maxMeasures);
    }
    */
}

DEF_CHOICE_8(       cMinMax,                                                                                              //--- ������� - ��� ���� ---
    "��� ����", "Min Max",
    "����� ���������� ��������� ���������, �� ������� �������� ��������������� �����, ��������� �������� � ��������� ���������.",
    "Sets number of the last measurements on which the limiting lines which are bending around minima and maxima of measurements are under "
    "construction."
    ,
    DISABLE_RU,DISABLE_EN,
    "2",   "2",
    "4",   "4",
    "8",   "8",
    "16",  "16",
    "32",  "32",
    "64",  "64",
    "128", "128",
    ENUM_MIN_MAX, pageDisplay, IsActive_MinMax, OnChanged_MinMax, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_REG_10(  cSmoothing,                                                                                        //--- ������� - ����������� ---
    "�����.", "Smoothing",
    "������������� ���������� ����� ��� ������� ����������� �� �������� ������ �������.",
    "Establishes quantity of points for calculation of the signal smoothed on the next points."
    ,
    DISABLE_RU, DISABLE_EN,
    "2 �����",  "2 points",
    "3 �����",  "3 points",
    "4 �����",  "4 points",
    "5 �����",  "5 points",
    "6 �����",  "6 points",
    "7 �����",  "7 points",
    "8 �����",  "8 points",
    "9 �����",  "9 points",
    "10 �����", "10 points",
    ENUM_SMOOTHING, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageDisplay::OnChanged_RefreshFPS(bool)
{
    FPGA::SetENumSignalsInSec(ENUM_SIGNALS_IN_SEC.ToFPS());
}

DEF_CHOICE_5(       cRefreshFPS,                                                                                    //--- ������� - ������� ������ ---
    "������� ������", "Refresh rate",
    "����� ������������ ����� ��������� � ������� ������.",
    "Sets the maximum number of the shots removed in a second.",
    "25", "25",
    "10", "10",
    "5",  "5",
    "2",  "2",
    "1",  "1",
    ENUM_SIGNALS_IN_SEC, pageDisplay, FuncActive, PageDisplay::OnChanged_RefreshFPS, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(       cScaleYtype,                                                                                          //--- ������� - �������� ---
    "��������", "�ffset",
    "����� ����� ��������� �������� �� ���������\n1. \"����������\" - ����������� ��������� ��������.\n2. \"�������\" - ����������� ��������� "
    "�������� �� ������.",
    "Sets the mode of retaining the vertical displacement\n1. \"Voltage\" - saved dressing bias.\n2. \"Divisions\" - retained the position of "
    "the offset on the screen.",
    "����������", "Voltage",
    "�������", "Divisions",
    LINKING_RSHIFT, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_10( pageDisplay,                                                                                                            //--- ������� ---
    "�������", "DISPLAY",
    "�������� ��������� ����������� �������.",
    "Contains settings of display of the display.",
    &cViewMode,                             ///< ������� - �����������
    PageDisplay::PageAccumulation::pointer, ///< ������� - ����������
    PageDisplay::PageAverage::pointer,      ///< ������� - ����������
    &cMinMax,                               ///< ������� - ��� ����
    &cSmoothing,                            ///< ������� - �����������
    &cRefreshFPS,                           ///< ������� - ������� ������
    PageDisplay::PageGrid::pointer,         ///< ������� - �����
    &cScaleYtype,                           ///< ������� - ��������
    &ppDisplaySettings,                     ///< ������� - ���������
    &cThickness,                            ///< ������� - �������
    Page::Name::Display, Menu::pageMain, FuncActive, EmptyPressPage
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_Brightness()
{
    Painter::SetBrightnessDisplay(BRIGHTNESS_DISPLAY);
}

DEF_GOVERNOR(       gSettings_Brightness,                                                                      //--- ������� - ��������� - ������� ---
    "�������", "Brightness",
    "��������� ������� �������� �������",
    "Setting the brightness of the display",
    BRIGHTNESS_DISPLAY, 0, 100, ppDisplaySettings, FuncActive, OnChanged_Settings_Brightness, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR(       gSettings_Levels,                                                                           //--- ������� - ��������� - ������ ---
    "������", "Levels",
    "����� �����, � ������� �������� ����� �������� ����� ������� ���������� �� ������ ������� ��������������� ����� ������ ��������",
    "Defines the time during which, after turning the handle visits to the voltage on the screen remains auxiliary label offset level",
    TIME_SHOW_LEVELS, 0, 125, ppDisplaySettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR(       gSettings_Time,                                                                              //--- ������� - ��������� - ����� ---
    "�����", "Time",
    "��������� �������, � ������� �������� ��������� ����� ���������� �� ������",
    "Set the time during which the message will be on the screen",
    TIME_MESSAGES, 1, 99, ppDisplaySettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(       cSettings_StringNavigation,                                                            //--- ������� - ��������� - ������ ���� ---
    "������ ����", "Path menu",
    "��� ������ \n����������\n ����� ������ ������ ��������� ������ ���� �� ������� �������� ����", /// \todo ��������� �������
    "When choosing \nDisplay\n at the top left of the screen displays the full path to the current page menu",
    "��������", "Temporary",    /// \todo ��������� �������
    "������", "All",
    "�������", "None",
    SHOW_STRING_NAVI, ppDisplaySettings, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AltMarkers(bool active)
{
    Display::ChangedRShiftMarkers(active);
}

DEF_CHOICE_3(       cSettings_AltMarkers,                                                                 //--- ������� - ��������� - ���. ������� ---
    "���. �������", "Alt. markers",
    "������������� ����� ����������� �������������� �������� ������� �������� � �������������:\n"
    "\"��������\" - �������������� ������� �� ������������,\n"
    "\"����������\" - �������������� ������� ������������ ������,\n"
    "\"����\" - �������������� ������� ������������ � ������� 5 ��� ����� �������� ����� �������� ������ �� ���������� ��� ������ �������������",
    "Sets the display mode of additional markers levels of displacement and synchronization:\n"
    "\"Hide\" - additional markers are not shown,\n"
    "\"Show\" - additional markers are shown always,\n"
    "\"Auto\" - additional markers are displayed for 5 seconds after turning the handle channel offset voltage or trigger level"
    ,
    "��������", "Hide",
    "����������", "Show",
    "����", "Auto",
    ALT_MARKERS, ppDisplaySettings, FuncActive, OnChanged_Settings_AltMarkers, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AutoHide(bool autoHide)
{
    Menu::SetAutoHide(autoHide);
}

DEF_CHOICE_6(cSettings_AutoHide,                                                                       //--- ������� - ��������� - �������� ---
    "��������", "Hide",
    "��������� ����� ���������� ������� ������ ��� �������� �����, �� ��������� �������� ���� ������������� ��������� � ������",
    "Installation after the last keystroke or turning the handle, after which the menu will automatically disappear",
    "�������", "Never",
    "����� 5 ���", "Through 5 s",
    "����� 10 ���", "Through 10 s",
    "����� 15 ���", "Through 15 s",
    "����� 30 ���", "Through 30 s",
    "����� 60 ���", "Through 60 s",
    MENU_AUTO_HIDE, ppDisplaySettings, FuncActive, OnChanged_Settings_AutoHide, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_7(         ppDisplaySettings,                                                                                      // ������� - ��������� ///
    "���������", "SETTINGS",
    "�������������� ��������� �������",
    "Additional display settings",
    PageDisplay::PageSettings::PageColors::pointer,     ///< ������� - ��������� - �����
    &gSettings_Brightness,                              ///< ������� - ��������� - �������
    &gSettings_Levels,                                  ///< ������� - ��������� - ������
    &gSettings_Time,                                    ///< ������� - ��������� - �����
    &cSettings_StringNavigation,                        ///< ������� - ��������� - ������ ����
    &cSettings_AltMarkers,                              ///< ������� - ��������� - ���. �������
    &cSettings_AutoHide,                                ///< ������� - ��������� - ��������
    Page::Name::Display_Settings, &pageDisplay, FuncActive, EmptyPressPage
)
