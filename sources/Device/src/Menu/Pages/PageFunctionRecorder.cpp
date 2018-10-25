#include "defines.h"
#include "PageFunction.h"
#include "Settings/Settings.h"
#include "Recorder/Recorder.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageRecorder;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cViewAlways,                                                                                     //--- ������� - ����������� - ������ ---
    "������", "Always",
    "��������� �������� ������ ������������ ��� ����������� ���� �����������",
    "Allows you to display data from the recorder when the recorder menu is off",
    DISABLE_RU, DISABLE_EN,
    ENABLE_RU,  ENABLE_EN,
    RECORDER_VIEW_ALLWAYS, pageRecorder, FuncActive, FuncChangedChoice, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_3( pageRecorder,                                                                                              //--- ������� - ����������� ---
    "�����������", "RECORDER",
    "������ � ��������������� �������� ������ � ��������",
    "Recording and playback of input signals and sensors",
    &cViewAlways,                                       ///< ������� - ����������� - ������
    PageFunction::PageRecorder::PageSource::pointer,    ///< ������� - ����������� - ��������
    PageFunction::PageRecorder::PageRecord::pointer,    ///< ������� - ����������� - ������
    Page::Name::Function_Recorder, PageFunction::pointer, FuncActive, FuncPress
)

const PageBase *PageFunction::PageRecorder::pointer = &pageRecorder;
