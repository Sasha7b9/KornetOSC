#include "defines.h"
#include "CPU.h"


#ifdef __cplusplus
extern "C" {
#endif

    //------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void MemManage_Handler()
    {
        while (1)
        {
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void UsageFault_Handler()
    {
        while (1)
        {
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void HardFault_Handler()
    {
        while (1)
        {
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void BusFault_Handler()
    {
        while (1)
        {
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    void PendSV_Handler()
    {
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    void NMI_Handler()
    {
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    void SVC_Handler()
    {
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------
    void DebugMon_Handler()
    {
    }

#ifdef __cplusplus
}
#endif