#pragma once
#include "defines.h"
#include "Settings/SettingsChannel.h"


/// ������������� �������� ��� �������� ����� ��������� - �� ������ ��� ���������
#define CURS_MOVEMENT               (set.curs_movement)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == Cursors::Movement::Percents)
/// ������� ������������ ��� �������� ����� ��������� � ������������� 1 �������
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == Cursors::Movement::Pixels)


/// ������� ������� ����������
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])


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

    /// �������� ������� ������� ����������
    static float PosU(Chan ch, int numCur);
};
