#pragma once
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PageFunction
{
public:
    static const PageBase *pointer;

    class FrequencyCounter
    {
    public:
        static const PageBase *pointer;

        /// \todo Здесь страшенный говнокод. Нельзя опускаться до персональных проверок

    /// Возвращает указатель на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Время счёта F
        static const Choice *GetChoiceTimeF();
        /// Возвращает указаетль на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Метки времени
        static const Choice *GetChoiceFreqClc();
        /// Возвращает указатель на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Кол-во периодов
        static const Choice *GetChoiceNumPeriods();
    };
};
