#pragma once


#define DAC_TRIGGER_NONE            0x00000000U
#define DAC_OUTPUTBUFFER_ENABLE     0x00000000U
#define DAC_CHANNEL_1               0x00000000U
#define DAC_CHANNEL_2               0x00000010U
#define DAC_OUTPUTBUFFER_DISABLE    0
#define DAC_ALIGN_8B_R              0x00000008U


typedef struct
{
    DAC_TypeDef                 *Instance;     /*!< Register base address             */
}DAC_HandleTypeDef;


HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef* hdac);
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef* hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);
