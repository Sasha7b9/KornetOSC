#pragma once

#include "stm32f4xx_hal_def.h"


typedef struct
{
    TIM_TypeDef                 *Instance;     /*!< Register base address             */
//    TIM_Base_InitTypeDef        Init;          /*!< TIM Time Base required parameters */
//    HAL_TIM_ActiveChannel       Channel;       /*!< Active channel                    */
    DMA_HandleTypeDef           *hdma[7];      /*!< DMA Handlers array
                                                   This array is accessed by a @ref DMA_Handle_index */
    HAL_LockTypeDef             Lock;          /*!< Locking object                    */
    //HAL_TIM_StateTypeDef   State;         /*!< TIM operation state               */
}TIM_HandleTypeDef;

