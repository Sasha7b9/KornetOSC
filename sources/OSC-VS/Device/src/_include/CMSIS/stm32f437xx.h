#pragma once

enum IRQn_Type
{
    NonMaskableInt_IRQn = -14
};

typedef struct
{
    volatile uint BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
} FMC_Bank1_TypeDef;
