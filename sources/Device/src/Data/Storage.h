#pragma once


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Storage
{
public:

    static void AddData(uint8 *dataA, uint8 *dataB, DataSettings ds);

    static bool GetData(DataSettings *ds);

    static int GetFrameP2P_RAM(DataSettings **ds, uint8 **dataA, uint8 **dataB);

    static int NumElementsInStorage();

    static DataSettings *DataSettingsFromEnd(int fromEnd);

    static uint8 *GetAverageData(Chan ch);

    static void GetDataFromEnd(int fromEnd, DataSettings *ds, uint8 *dataA, uint8 *dataB);

    static bool GetLimitation(Chan ch, uint8 *data, int direction);
};
