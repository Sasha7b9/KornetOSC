#include "defines.h"
#include "main.h"
#include "Log.h"
#include "Device.h"
#include "Hardware/AT25160N.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Device::Init();

    //AT25160N::Init();

    while (1)
    {
        Device::Update();

//        AT25160N::Test();
    }
}
