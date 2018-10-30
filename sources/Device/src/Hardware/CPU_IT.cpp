#include "defines.h"
#include "Sound.h"
#include "FPGA/FPGA.h"


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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(FPGA::HandleADC());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    /// \todo временная затычка. Не в рандомизаторе эта функция вообще не должна вызываться

    if (IN_RANDOM_MODE)
    {
        FPGA::SetValueADC((uint16)HAL_ADC_GetValue(hadc));
    }
}

#ifdef __cplusplus
}
#endif
