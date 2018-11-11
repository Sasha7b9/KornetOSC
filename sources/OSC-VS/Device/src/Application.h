#pragma once
#include "wx/wxprec.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
    ID_ENTER = 100
};

class Application : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Frame : public wxFrame
{
public:
    Frame(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

private:
    wxTimer timer;
    wxDECLARE_EVENT_TABLE();

    void DrawFPS();
    void HandlerEvents();

    void OnPressEnter(wxCommandEvent &event);

public:
    void OnDown(wxCommandEvent &event);
    void OnUp(wxCommandEvent &event);
};
