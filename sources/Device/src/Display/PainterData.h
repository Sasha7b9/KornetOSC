#pragma once
#include "defines.h"
#include "FPGA/FPGATypes.h"
#include "Settings/SettingsTypes.h"
#include "Data/Reader.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PainterData
{
public:
    
    static void DrawData();

    static void DrawChannel(Channel ch, uint8 data[FPGA_MAX_NUM_POINTS]);

private:
    
    static void DrawData_ModeDir();

    static void DrawMemoryWindow();

    static void DrawDataInRect(int x, int y, int width, int height, Channel ch);

    static void DrawTPos(int leftX, int rightX);

    static void DrawTShift(int leftX, int rightX, int numPoints);
    /// ���������� (-1), ���� ����� �� ������� (NONE_VALUE)
    static int Ordinate(uint8 x, float scale);
    /// \brief ���������� ����� � �������� ����������. ���� ����� �� ������� (NONE_VALUE), ���������� -1.
    /// ��������� ������������ width ������ 255.
    static void SendToDisplayDataInRect(Channel chan, int x, int *min, int *max, int width);

    static StructDataDrawing *dataStruct;
};
