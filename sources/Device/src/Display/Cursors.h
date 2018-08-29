#pragma once
#include "defines.h"
#include "Settings/SettingsChannel.h"


/// ������������� �������� ��� �������� ����� ��������� - �� ������ ��� ���������
#define CURS_MOVEMENT               (set.curs_movement)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == Cursors::Movement::Percents)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1 �������
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == Cursors::Movement::Pixels)

/// ������ ��������� ��������� ����� ���������
#define CURS_ACTIVE                 (set.curs_active)
/// ����� ��������� ��������� ��������� ����������
#define CURS_ACTIVE_U               (CURS_ACTIVE == Cursors::Active::U)
/// ����� ��������� ��������� ��������� �������
#define CURS_ACTIVE_T               (CURS_ACTIVE == Cursors::Active::T)


/// ������� ������� ����������
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])
/// ������� ������� �������
#define CURsT_POS(ch, num)          Cursors::PosT(ch, num)


class Cursors
{
public:
    /// ������������ ����������� ��������.
    struct Movement
    {
        enum E
        {
            Pixels,    ///< �� �������� ������
            Percents   ///< �� ���������
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ����� ������� ������ �������. ����� �������, �� � ����� ������������ �� �������� ����� ���������.
    struct Active
    {
        enum E
        {
            U,
            T,
            None
        } value;
        Active(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
    };

    /// �������� ������� ������� ����������
    static float PosU(Chan ch, int numCur);
    /// ���������� true,���� ����� �������� �������
    static bool  NecessaryDraw();
    /// �������� ������ ������� ����������
    static pString Voltage(Chan source, int numCur, char buffer[20]);
    /// ���������� �������� ������� �������
    static float PosT(Chan ch, int num);
};
