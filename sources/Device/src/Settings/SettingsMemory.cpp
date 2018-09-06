#include "SettingsMemory.h"
#include "Data/Reader.h"
#include "FPGA/FPGATypes.h"
#include "Settings/Settings.h"
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sMemory_NumBytesInChannel_()
{
    DataSettings ds;
    ds.Fill();
    return ds.BytesInChannel();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ENumPointsFPGA NumPoints_2_ENumPoints(int numPoints)
{
    if (numPoints == 8192)  { return ENumPointsFPGA::_8k; }
    else if (numPoints == 4096)  { return ENumPointsFPGA::_4k; }
    else if (numPoints == 2048)  { return ENumPointsFPGA::_2k; }
    else if (numPoints == 1024)  { return ENumPointsFPGA::_1k; }
    return ENumPointsFPGA::_512;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int ENumPoints_2_NumPoints(ENumPointsFPGA numPoints)
{
    static const int n[ENumPointsFPGA::Size] =
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
void *AllocMemForChannelFromHeap(Chan ch, DataSettings *ds)
{
    int numBytes = RequestBytesForChannel(ch, ds);
    if (numBytes)
    {
        return malloc((uint)numBytes);
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
int RequestBytesForChannel(Chan, DataSettings *ds)
{
    ENumPointsFPGA numBytes;
    PeakDetMode peakDet;

    if (ds)
    {
        numBytes = (ENumPointsFPGA::E)(ENUM_BYTES(ds));
        peakDet = PEAKDET(ds);
    }
    else
    {
        numBytes = NumPoints_2_ENumPoints(NUM_BYTES(ds));
        peakDet = SET_PEAKDET;
    }

    return FPGA_MAX_NUM_POINTS;
}
