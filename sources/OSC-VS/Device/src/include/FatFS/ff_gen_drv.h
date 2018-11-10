#pragma once

#include "diskio.h"
#include "ff.h"
#include "stdint.h"


typedef struct
{
    uint i = 0;
//     DSTATUS(*disk_initialize) (BYTE);                     /*!< Initialize Disk Drive                     */
//     DSTATUS(*disk_status)     (BYTE);                     /*!< Get Disk Status                           */
//     DRESULT(*disk_read)       (BYTE, BYTE*, DWORD, UINT);       /*!< Read Sector(s)                            */
// #if _USE_WRITE == 1
//     DRESULT(*disk_write)      (BYTE, const BYTE*, DWORD, UINT); /*!< Write Sector(s) when _USE_WRITE = 0       */
// #endif /* _USE_WRITE == 1 */
// #if _USE_IOCTL == 1
//     DRESULT(*disk_ioctl)      (BYTE, BYTE, void*);              /*!< I/O control operation when _USE_IOCTL = 1 */
// #endif /* _USE_IOCTL == 1 */

}Diskio_drvTypeDef;
