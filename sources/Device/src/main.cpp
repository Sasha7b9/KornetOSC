#include "defines.h"
#include "main.h"
#include "Log.h"
#include "Device.h"
#include "Hardware/AT25160N.h"
#include "Hardware/Timer.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Device::Init();

    AT25160N::Init();

    Device::ChangeMode();

    while (1)
    {
        Device::Update();
    }
}
