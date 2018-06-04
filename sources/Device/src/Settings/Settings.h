#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Menu/MenuItems.h"
#include "SettingsTime.h"
#include "SettingsMemory.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TESTER_NUM_POINTS               (240)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MATH_FUNC_IS_SUM                false
#define MATH_FUNC_IS_MUL                false

#define SET_COUPLE(ch)                  (set.chan_couple[ch])
#define SET_COUPLE_A                    (SET_COUPLE(A))
#define SET_COUPLE_B                    (SET_COUPLE(B))
#define SET_RSHIFT(ch)                  (set.chan_shift[ch])
#define SET_RANGE(ch)                   (set.chan_range[ch])
#define SET_RANGE_A                     (SET_RANGE(A))
#define SET_RANGE_B                     (SET_RANGE(B))
#define LANG                            (set.serv_lang)
#define LANG_RU                         (LANG == RU)
#define SET_TRIGLEV                     (set.trig_lev)
#define IN_RANDOMIZE_MODE               (SET_TBASE < TBase_100ns)
#define CURRENT_PAGE                    (set.menu_currentPage)
#define SET_ENABLED(ch)                 (set.chan_enable[ch])

#define VIEW_MODE                       (set.disp_modeDrawSignal)
#define VIEW_MODE_IS_LINES              (VIEW_MODE == Mode_Lines)
#define THICKNESS_SIGNAL                (set.disp_thickness)
#define THICKNESS_SIGNAL_IS_3           (THICKNESS_SIGNAL == Thickness_3)

#define TRIG_MODE                       (set.trig_mode)
#define TRIG_SOURCE                     (set.trig_source)
#define TRIG_POLARITY                   (set.trig_polarity)
#define TRIG_POLARITY_IS_RISING         (TRIG_POLARITY == Polarity_Rising)
#define TRIG_INPUT                      (set.trig_input)

#define TESTER_CONTROL                  (set.test_control)
#define TESTER_CONTROL_IS_U             (TESTER_CONTROL == Control_Voltage)
#define TESTER_POLARITY                 (set.test_polarity)
#define TESTER_POLARITY_IS_POSITITVE    (TESTER_POLARITY == Polarity_Positive)
#define TESTER_STEP_U                   (set.test_stepU)
#define TESTER_STEP_I                   (set.test_stepI)
#define TESTER_NUM_SMOOTH               (set.test_smooth)

#define MENU_IS_SHOWN                   (set.menu_show)


/// ���������� ������� ��������� ������ �� �������� namePage.
#define MENU_POS_ACT_ITEM(name)     (set.menu_PosActItem[name])
/// ������� �����������
#define MENU_CURRENT_SUBPAGE(name)  (set.menu_CurrentSubPage[name])

#pragma pack(push, 1)


#define COLOR(x) GlobalColors[x]

extern uint GlobalColors[32];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings
{
public:
    static void Load();
    static void Save();
    static void Reset();

    uint            size;                       ///< ������ ������ ��������� � ������
    uint            crc32;                      ///< \brief ����������� ����� ������ ��������� � ����������� � ��� �����������. ����������� ����� 
                                                ///< ����������� �� ������� �����, ���������� �� ���� �����
    ModeDrawSignal  disp_modeDrawSignal;
    ThicknessSignal disp_thickness;             ///< ������� �����, ������� �������� ������
    uint16          chan_shift[NumChannels];    ///< ����� ������ �� ���������
    Range           chan_range[NumChannels];    ///< ������� ������ �� ���������
    Couple          chan_couple[NumChannels];   ///< ����� �� �����
    bool            chan_enable[NumChannels];   ///< �������/�������� �����
    Channel         trig_source;
    TrigInput       trig_input;
    TrigPolarity    trig_polarity;
    uint16          trig_lev;
    ModeTrig        trig_mode;
    Language        serv_lang;
    uint16          time_shift;
    TBase           time_base;
    TesterControl   test_control;
    TesterPolarity  test_polarity;
    TesterStepU     test_stepU;
    TesterStepI     test_stepI;
    uint8           test_smooth;                        ///< ���������� �����������
    EnumPoints      mem_enumPoints;                     ///< ����� �����
    const Page     *menu_currentPage;                   ///< ��������� �� �������� �������� ����
    bool            menu_show;                          ///< ���� true, �� ����� ���������� ������� ��������
    int8            menu_PosActItem[Page_NumPages];     ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� 
                                                        ///< ��������� ������.
    int8            menu_CurrentSubPage[Page_NumPages]; ///< ����� ������� �����������.
    Background      disp_Background;                    ///< ���� ����.
};

#pragma pack(pop)

extern Settings set;
