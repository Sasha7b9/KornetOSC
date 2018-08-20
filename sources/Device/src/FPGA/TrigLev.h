#pragma once
#include "defines.h"


class TrigLev
{

friend class FPGA;

public:
    static const int MIN = 20;
    static const int MAX = 980;
    static const int ZERO = 500;
    /// ���������� true � ������ ������� ��������������
    static bool SyncPulse();

private:
    /// ������������� � true �������� ��������, ��� ����� �������� ������ ��������������
    static bool pulse;
    /// ����� ��������������� �������
    static uint timeSwitchingTrig;
};
