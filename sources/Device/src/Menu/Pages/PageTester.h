#pragma once
#include "Menu/MenuItems.h"


class PageTester
{
public:

    static void Init();

    static void OnChanged_Control(bool);

    static const PageBase *pointer;
};
