#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PageMeasures
{
public:
    static const PageBase *pointer;

    static const PageBase *GetPageFrequencyCounter();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PageFrequencyCounter
{

    /// \todo Здесь страшенный говнокод. Нельзя опускаться до персональных проверок

public:
    static const PageBase *pointer;
    /// Возвращает указатель на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Время счёта F
    static const Choice *GetChoiceTimeF();
    /// Возвращает указаетль на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Метки времени
    static const Choice *GetChoiceFreqClc();
    /// Возвращает указатель на ИЗМЕРЕНИЯ - ЧАСТОТОМЕР - Кол-во периодов
    static const Choice *GetChoiceNumPeriods();
};
