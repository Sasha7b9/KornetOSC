#include "Sound.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DMA1_Stream5_IRQHandler()
{
    HAL_DMA_IRQHandler(Sound::handleDAC.DMA_Handle1);
}
