/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : nrf52840_spim.h
Purpose : SPIM header file

*/


#ifndef NRF52840_SPIM_H
#define NRF52840_SPIM_H


#include "nrf52840.h"



/******************************************************************************
 * Some Common Macros
 ******************************************************************************/

/* ---------------------------- NC Macro ---------------------------- */

#define SPIM_PIN_NOT_CONNECTED          0xFFFFFFFFUL

/* ---------------------------- Instance macro ---------------------------- */

#define SPIM_INSTANCE(Id)              \
{                                      \
    .Instance     = SPIM##Id           \
    .drv_inst_idx = Id                 \
    .State        = SPIM_READY         \
} 
                              
/* ---------------------------- Config Macros ---------------------------- */

#define SPIM_DEFAULT_CONFIG(sck,mosi,miso) \
{                                          \
    .SCK_Pin   = (sck),                    \
    .MOSI_Pin  = (mosi),                   \
    .MISO_Pin  = (miso),                   \
    .Frequency = SPIM_FREQ_1M,             \
    .Mode      = SPIM_MODE0,               \
    .BitOrder  = SPIM_MSB_FIRST            \
}

#define SPIM_EPD_CONFIG(sck,mosi,miso) \
{                                      \
    .SCK_Pin   = (sck),                \
    .MOSI_Pin  = (mosi),               \
    .MISO_Pin  = SPIM_PIN_NOT_CONNECTED,\
    .Frequency = SPIM_FREQ_4M,         \
    .Mode      = SPIM_MODE0,           \
    .BitOrder  = SPIM_MSB_FIRST        \
}

#define SPIM_FLASH_CONFIG(sck,mosi,miso) \
{                                        \
    .SCK_Pin   = (sck),                  \
    .MOSI_Pin  = (mosi),                 \
    .MISO_Pin  = (miso),                 \
    .Frequency = SPIM_FREQ_8M,           \
    .Mode      = SPIM_MODE0,             \
    .BitOrder  = SPIM_MSB_FIRST          \
}

#define SPIM_LORA_CONFIG(sck,mosi,miso) \
{                                       \
    .SCK_Pin   = (sck),                 \
    .MOSI_Pin  = (mosi),                \
    .MISO_Pin  = (miso),                \
    .Frequency = SPIM_FREQ_1M,          \
    .Mode      = SPIM_MODE0,            \
    .BitOrder  = SPIM_MSB_FIRST         \
}

#define SPIM_SENSOR_CONFIG(sck,mosi,miso) \
{                                         \
    .SCK_Pin   = (sck),                   \
    .MOSI_Pin  = (mosi),                  \
    .MISO_Pin  = (miso),                  \
    .Frequency = SPIM_FREQ_500K,          \
    .Mode      = SPIM_MODE0,              \
    .BitOrder  = SPIM_MSB_FIRST           \
}


/******************************************************************************
 * Enumerations
 ******************************************************************************/

/* ---------------------------- Frequency Enum ---------------------------- */
 typedef enum
{
    SPIM_FREQ_125K = 0x02000000,
    SPIM_FREQ_250K = 0x04000000,
    SPIM_FREQ_500K = 0x08000000,
    SPIM_FREQ_1M   = 0x10000000,
    SPIM_FREQ_2M   = 0x20000000,
    SPIM_FREQ_4M   = 0x40000000,
    SPIM_FREQ_8M   = 0x80000000
} SPIM_Frequency_t;

/* ---------------------------- Mode Enum ---------------------------- */

typedef enum
{
    SPIM_MODE0 = 0,    // CPOL=0 CPHA=0
    SPIM_MODE1,
    SPIM_MODE2,
    SPIM_MODE3
} SPIM_Mode_t;

/* ---------------------------- Bit Order Enum ---------------------------- */

typedef enum
{
    SPIM_MSB_FIRST = 0,
    SPIM_LSB_FIRST = 1
} SPIM_BitOrder_t;

/* ---------------------------- State Enum ---------------------------- */

typedef enum
{
    SPIM_READY = 0,
    SPIM_BUSY_TX,
    SPIM_BUSY_RX,
    SPIM_BUSY_TXRX
} SPIM_State_t;

/* ---------------------------- Status Enum ---------------------------- */

typedef enum
{
    SPIM_SUCCESS = 0,
    SPIM_ERROR_INVALID_PARAM,
    SPIM_ERROR_BUSY,
    SPIM_ERROR_TIMEOUT,
    SPIM_ERROR_NULL_PTR
} SPIM_Status_t;

 /******************************************************************************
 * Structures
 ******************************************************************************/

/* ---------------------------- Config Structure ---------------------------- */

typedef struct{

    uint32_t SCK_Pin;

    uint32_t MOSI_Pin;

    uint32_t MISO_Pin;

    SPIM_Frequency_t Frequency;

    SPIM_Mode_t Mode;

    SPIM_BitOrder_t BitOrder;

}SPIM_Config_t;

/* ---------------------------- Handle Structure ---------------------------- */

typedef struct{

    NRF_SPIM_RegDef_t *Instance;

    uint32_t drv_inst_idx;

    volatile SPIM_State_t State;

}SPIM_Handle_t;


/******************************************************************************
 * Function Declaration
 ******************************************************************************/

SPIM_Status_t SPIM_Init(
    SPIM_Handle_t *p_instance,
    SPIM_Config_t *p_config);

SPIM_Status_t SPIM_DeInit(
    SPIM_Handle_t *p_instance);

SPIM_Status_t SPIM_Transmit(
    SPIM_Handle_t *p_instance,
    uint8_t *p_tx_buf,
    uint16_t length);

SPIM_Status_t SPIM_Receive(
    SPIM_Handle_t *p_instance,
    uint8_t *p_rx_buf,
    uint16_t length);

SPIM_Status_t SPIM_Transfer(
    SPIM_Handle_t *p_instance,
    uint8_t *p_tx_buf,
    uint8_t *p_rx_buf,
    uint16_t length);

void SPIM_Stop(
    SPIM_Handle_t *p_instance);

void SPIM_Suspend(
    SPIM_Handle_t *p_instance);

void SPIM_Resume(
    SPIM_Handle_t *p_instance);



#endif


/******************************* END OF FILE *********************************/