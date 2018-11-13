#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Buffer.h"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_BUFFER (32 * 1024)

static uint8 buffer[SIZE_BUFFER];


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Buffer::Init()
{
    for(int i = 0; i < SIZE_BUFFER; i++)
    {
        buffer[i] = (uint8)i;
    }
}
