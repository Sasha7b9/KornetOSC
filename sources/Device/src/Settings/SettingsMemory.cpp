#include "SettingsMemory.h"
#include "Data/Reader.h"
#include "FPGA/FPGATypes.h"
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sMemory_NumPointsInChannel_()
{
    static const int numPoints[FPGA_ENUM_POINTS_SIZE] =
    {
        512,
        1024,
        2048,
        4096,
        8192
    };

    return numPoints[FPGA_ENUM_POINTS];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int sMemory_NumBytesInChannel_()
{
    DataSettings ds;
    ds.Fill();
    return ds.BytesInChannel();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ENumPointsFPGA NumPoints_2_ENumPoints(int numPoints)
{
    if (numPoints == 8192)  { return FNP_8k; }
    else if (numPoints == 4096)  { return FNP_4k; }
    else if (numPoints == 2048)  { return FNP_2k; }
    else if (numPoints == 1024)  { return FNP_1k; }
    return FNP_512;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int ENumPoints_2_NumPoints(ENumPointsFPGA numPoints)
{
    static const int n[FPGA_ENUM_POINTS_SIZE] =
    {
        512,
        1024,
        2048,
        4096,
        8192
    };
    return n[(uint)numPoints];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void *AllocMemForChannelFromHeap(Channel ch, DataSettings *ds)
{
    int numBytes = RequestBytesForChannel(ch, ds);
    if (numBytes)
    {
        return malloc((uint)numBytes);
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
int RequestBytesForChannel(Channel, DataSettings *ds)
{
    volatile ENumPointsFPGA numBytes;
    volatile PeakDetMode peakDet;

    if (ds)
    {
        numBytes = (ENumPointsFPGA)ENUM_BYTES(ds);
        peakDet = PEAKDET(ds);
    }
    else
    {
        numBytes = NumPoints_2_ENumPoints(NUM_BYTES(ds));
        peakDet = SET_PEAKDET;
    }

    return FPGA_MAX_NUM_POINTS;
}
