#pragma once


typedef union
{
    uint16_t w;
    struct BW
    {
        uint8_t msb;
        uint8_t lsb;
    }
    bw;
}
uint16_t_uint8_t;


typedef union _USB_Setup
{
    uint32_t d8[2];

    struct _SetupPkt_Struc
    {
        uint8_t           bmRequestType;
        uint8_t           bRequest;
        uint16_t_uint8_t  wValue;
        uint16_t_uint8_t  wIndex;
        uint16_t_uint8_t  wLength;
    } b;
}
USB_Setup_TypeDef;

typedef enum
{
    CTRL_IDLE = 0,
    CTRL_SETUP,
    CTRL_SETUP_WAIT,
    CTRL_DATA_IN,
    CTRL_DATA_IN_WAIT,
    CTRL_DATA_OUT,
    CTRL_DATA_OUT_WAIT,
    CTRL_STATUS_IN,
    CTRL_STATUS_IN_WAIT,
    CTRL_STATUS_OUT,
    CTRL_STATUS_OUT_WAIT,
    CTRL_ERROR,
    CTRL_STALLED,
    CTRL_COMPLETE
}CTRL_StateTypeDef;

typedef struct
{
    uint8_t               pipe_in;
    uint8_t               pipe_out;
    uint8_t               pipe_size;
    uint8_t               *buff;
    uint16_t              length;
    uint16_t              timer;
    USB_Setup_TypeDef     setup;
    CTRL_StateTypeDef     state;
    uint8_t               errorcount;

} USBH_CtrlTypeDef;

typedef enum
{
    CMD_IDLE = 0,
    CMD_SEND,
    CMD_WAIT
} CMD_StateTypeDef;

typedef enum
{
    ENUM_IDLE = 0,
    ENUM_GET_FULL_DEV_DESC,
    ENUM_SET_ADDR,
    ENUM_GET_CFG_DESC,
    ENUM_GET_FULL_CFG_DESC,
    ENUM_GET_MFC_STRING_DESC,
    ENUM_GET_PRODUCT_STRING_DESC,
    ENUM_GET_SERIALNUM_STRING_DESC,
} ENUM_StateTypeDef;


typedef enum
{
    HOST_IDLE = 0,
    HOST_DEV_WAIT_FOR_ATTACHMENT,
    HOST_DEV_ATTACHED,
    HOST_DEV_DISCONNECTED,
    HOST_DETECT_DEVICE_SPEED,
    HOST_ENUMERATION,
    HOST_CLASS_REQUEST,
    HOST_INPUT,
    HOST_SET_CONFIGURATION,
    HOST_CHECK_CLASS,
    HOST_CLASS,
    HOST_SUSPENDED,
    HOST_ABORT_STATE,
}HOST_StateTypeDef;

typedef struct
{
#if (USBH_KEEP_CFG_DESCRIPTOR == 1)  
    uint8_t                           CfgDesc_Raw[USBH_MAX_SIZE_CONFIGURATION];
#endif  
    uint8_t                           Data[USBH_MAX_DATA_BUFFER];
    uint8_t                           address;
    uint8_t                           speed;
    __IO uint8_t                      is_connected;
    uint8_t                           current_interface;
    USBH_DevDescTypeDef               DevDesc;
    USBH_CfgDescTypeDef               CfgDesc;

}USBH_DeviceTypeDef;


typedef struct _USBH_HandleTypeDef
{
  HOST_StateTypeDef     gState;        /*  Host State Machine Value */
  ENUM_StateTypeDef     EnumState;          /* Enumeration state Machine */
  CMD_StateTypeDef      RequestState;       
  USBH_CtrlTypeDef      Control;
  USBH_DeviceTypeDef    device;
  USBH_ClassTypeDef*    pClass[USBH_MAX_NUM_SUPPORTED_CLASS];
  USBH_ClassTypeDef*    pActiveClass;
  uint32_t              ClassNumber;
  uint32_t              Pipes[15];
  uint32_t              Timer;
  uint8_t               id;  
  void*                 pData;                  
  void                 (* pUser )(struct _USBH_HandleTypeDef *pHandle, uint8_t id);
  
#if (USBH_USE_OS == 1)
  osMessageQId          os_event;   
  osThreadId            thread; 
#endif  
  
} USBH_HandleTypeDef;
