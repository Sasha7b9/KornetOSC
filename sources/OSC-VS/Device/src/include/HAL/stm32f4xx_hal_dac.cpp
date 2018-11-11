#include "stdafx.h"
#include "stm32f4xx_hal_dac.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *, uint32_t, uint32_t, uint32_t)
{
    return HAL_ERROR;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *, uint32_t)
{
    return HAL_OK;
}
