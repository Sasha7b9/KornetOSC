#pragma once
#include "Menu/MenuItems.h"


class PageMultimeter
{
public:
    static void Init();

    static void OnChanged_Mode(bool);

    static const PageBase *pointer;
};
