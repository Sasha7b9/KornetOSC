#pragma once

#include "stm32f4xx.h"
#include "Legacy/stm32_hal_legacy.h"

typedef enum
{
    HAL_UNLOCKED = 0x00U,
    HAL_LOCKED = 0x01U
} HAL_LockTypeDef;

