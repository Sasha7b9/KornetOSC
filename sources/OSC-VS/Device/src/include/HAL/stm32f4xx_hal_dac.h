#pragma once


#define DAC_TRIGGER_NONE        0x00000000U
#define DAC_OUTPUTBUFFER_ENABLE 0x00000000U
#define DAC_CHANNEL_1           0x00000000U
#define DAC_CHANNEL_2           0x00000010U


typedef struct
{
    DAC_TypeDef                 *Instance;     /*!< Register base address             */
}DAC_HandleTypeDef;


HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef* hdac);
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel);
