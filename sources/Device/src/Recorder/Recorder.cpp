#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Settings/Settings.h"
#include "Recorder.h"
#include "Display/Painter.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Recorder::Init()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recorder::Graphics::Update()
{
    Painter::BeginScene(Color::BLUE_10);
}
