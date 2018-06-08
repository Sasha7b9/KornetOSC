#include "MenuTriggers.h"
#include "Globals.h"
#include "Display/Display.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      Key TriggerDebugConsole::bufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {Key::None};
const Key TriggerDebugConsole::sampleBufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {Key::F5, Key::F5, Key::F4, Key::F4, Key::F3, Key::F3, Key::F2, 
                                                                                    Key::F2, Key::F1,  Key::F1};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TriggerDebugConsole::Update(Key button)
{
    for (int i = SIZE_BUFFER_FOR_BUTTONS - 1; i > 0; i--)
    {
        bufferForButtons[i] = bufferForButtons[i - 1];
    }
    bufferForButtons[0] = button;

    if (memcmp(bufferForButtons, sampleBufferForButtons, SIZE_BUFFER_FOR_BUTTONS) == 0)
    {
        SHOW_DEBUG_MENU = 1;
        Display::ShowWarning(MenuDebugEnabled);
    }
}
