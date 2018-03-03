#include "Hardware.h"
#include "FSMC.h"
#include "Display/Display.h"
#include "Keyboard/Keyboard.h"
#include "Hardware/CPU.h"
#include <stm32f4xx_hal.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Hardware hardware;

//static void ConfigSystemClock1(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hardware::Init()
{
    CPU::Init();

    Display::Init();
    
    Keyboard::Init();

    FSMC::Init();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Hardware::ResetPin(GPIO_TypeDef *port, uint16 numPin)
{
    HAL_GPIO_WritePin(port, numPin, GPIO_PIN_RESET);
}
