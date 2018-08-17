#include "TShift.h"
#include "defines.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TShift::Min()
{

#define k 0

    static const int m[ENumPointsFPGA::Size][3] =
    {
        {-256 + k,  -128 + k,  0 + k},  // 512
        {-512 + k , -256 + k,  0 + k},  // 1024
        {-1024 + k, -512 + k,  0 + k},  // 2048
        {-2048 + k, -1024 + k, 0 + k},  // 4096
        {-4096 + k, -2048 + k, 0 + k},  // 8192
        {-8192 + k, -4096 + k, 0 + k}   // 16384
    };

    if (SET_PEAKDET_DIS)
    {
        return m[FPGA_ENUM_POINTS][TPOS];
    }

    return m[FPGA_ENUM_POINTS][TPOS] * 2; // ��� �������� ��������� ��� �������� ������ ���� � ��� ���� ������
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int TShift::Zero()
{
    return -Min();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int TShift::Max()
{
    return 60000;
}