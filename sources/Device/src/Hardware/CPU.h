#pragma once
#include "Hardware/stm32/stm437.h"


class CPU : public STM437
{
public:

    static void Init();
};
