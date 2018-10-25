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

        /// \todo ����� ���������� ��������. ������ ���������� �� ������������ ��������

    /// ���������� ��������� �� ��������� - ���������� - ����� ����� F
        static const Choice *GetChoiceTimeF();
        /// ���������� ��������� �� ��������� - ���������� - ����� �������
        static const Choice *GetChoiceFreqClc();
        /// ���������� ��������� �� ��������� - ���������� - ���-�� ��������
        static const Choice *GetChoiceNumPeriods();
    };
};
