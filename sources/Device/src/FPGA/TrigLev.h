#pragma once
#include "defines.h"


class Trig
{

friend class FPGA;

public:
    static const int MIN = 20;
    static const int MAX = 980;
    static const int ZERO = 500;
    /// ���������� true � ������ ������� ��������������
    static bool SyncPulse();

    /// �������� �������������
    struct Source
    {
        enum E
        {
            A,    /// ����� 1
            B,    /// ����� 2
            Ext   /// �������
        } value;
        operator uint8() const { return (uint8)value; }
    };

    /// ����� �������.
    struct StartMode
    {
        enum E
        {
            Auto,     ///< ��������������.
            Wait,     ///< ������.
            Single    ///< �����������.
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct ModeFind
    {
        enum E
        {
            Hand,      ///< ������� ������������� ��������������� ������� ��� ������������� - ����������� ��������� ������.
            Auto       ///< ���������� ������ ������������� ������������ ������������� ����� ������� ������ ���������� �������.
        } value;
        operator uint8() const { return (uint8)value; };
    };

private:
    /// ������������� � true �������� ��������, ��� ����� �������� ������ ��������������
    static bool pulse;
    /// ����� ��������������� �������
    static uint timeSwitchingTrig;
};
