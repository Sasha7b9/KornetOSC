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

    /// \todo ����� ���������� ��������. ������ ���������� �� ������������ ��������

public:
    static const PageBase *pointer;
    /// ���������� ��������� �� ��������� - ���������� - ����� ����� F
    static const Choice *GetChoiceTimeF();
    /// ���������� ��������� �� ��������� - ���������� - ����� �������
    static const Choice *GetChoiceFreqClc();
    /// ���������� ��������� �� ��������� - ���������� - ���-�� ��������
    static const Choice *GetChoiceNumPeriods();
};
