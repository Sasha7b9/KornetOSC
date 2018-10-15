#include "defines.h"
#include "Sound.h"
#include "Multimeter/Multimeter.h"

#ifdef __cplusplus
extern "C" {
#endif
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DMA1_Stream5_IRQHandler()
{
    HAL_DMA_IRQHandler(Sound::handleDAC.DMA_Handle1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void USART3_IRQHandler(void)
{
    HAL_UART_IRQHandler(&Multimeter::handlerUART);
}

#ifdef __cplusplus
}
#endif
