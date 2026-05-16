/*
 * stm32f303xx_can_driver.h
 *
 *  Created on: Jan 31, 2026
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_CAN_DRIVER_H_
#define INC_STM32F303XX_CAN_DRIVER_H_

typedef struct
{
    /* -------- Bit Timing -------- */
    uint16_t Prescaler;
    uint8_t  SJW;
    uint8_t  BS1;
    uint8_t  BS2;

    /* -------- Operating Mode -------- */
    uint8_t  Mode;

    /* -------- Feature Control -------- */
    uint8_t  TTCM;
    uint8_t  ABOM;
    uint8_t  AWUM;
    uint8_t  NART;
    uint8_t  RFLM;
    uint8_t  TXFP;

} CAN_Config_t;



typedef struct
{
    uint8_t FilterBank;
    uint8_t FilterMode;
    uint8_t FilterScale;

    union
    {
        struct   // 32-bit scale
        {
            uint32_t ID1;
            uint32_t ID2;   // or MASK depending on mode
        } Scale32;

        struct   // 16-bit scale
        {
            uint16_t ID1;
            uint16_t ID2;
            uint16_t ID3;
            uint16_t ID4;
        } Scale16;
    };

    uint8_t FIFOAssignment;
    uint8_t Activation;

} CAN_FilterConfig_t;



typedef struct
{
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t  IDE;
    uint8_t  RTR;
    uint8_t  DLC;
    uint8_t  TGT;

} CAN_TxHeader_t;


typedef struct
{
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t  IDE;
    uint8_t  RTR;
    uint8_t  DLC;
    uint16_t TimeStamp;
    uint8_t  FMI;

} CAN_RxHeader_t;

typedef enum
{
    CAN_OK = 0,
    CAN_ERROR,
    CAN_ERROR_TIMEOUT,
    CAN_ERROR_BUSY,
	CAN_ERROR_EMPTY,
    CAN_ERROR_INVALID_PARAM,
	CAN_PENDING

} CAN_Status_t;


typedef enum
{
	CAN_STATE_RESET = 0,
    CAN_STATE_INIT,
    CAN_STATE_NORMAL,
    CAN_STATE_SLEEP

} CAN_State_t;


typedef struct
{
    CAN_Regs_t     *pCANx;       // Peripheral base address
    CAN_Config_t    Config;        // Init configuration
    CAN_State_t     State;       // Driver state
    uint32_t        ErrorCode;   // Error tracking

} CAN_Handle_t;



/* ===== CAN Operating Modes ===== */

#define CAN_MODE_NORMAL              0x00U
#define CAN_MODE_LOOPBACK            0x01U
#define CAN_MODE_SILENT              0x02U
#define CAN_MODE_SILENT_LOOPBACK     0x03U

/* ===== Synchronization Jump Width ===== */

#define CAN_SJW_1TQ    0x00U
#define CAN_SJW_2TQ    0x01U
#define CAN_SJW_3TQ    0x02U
#define CAN_SJW_4TQ    0x03U

/* ===== Time Segment 1 ===== */

#define CAN_BS1_1TQ     0x00U
#define CAN_BS1_2TQ     0x01U
#define CAN_BS1_3TQ     0x02U
#define CAN_BS1_4TQ     0x03U
#define CAN_BS1_5TQ     0x04U
#define CAN_BS1_6TQ     0x05U
#define CAN_BS1_7TQ     0x06U
#define CAN_BS1_8TQ     0x07U
#define CAN_BS1_9TQ     0x08U
#define CAN_BS1_10TQ    0x09U
#define CAN_BS1_11TQ    0x0AU
#define CAN_BS1_12TQ    0x0BU
#define CAN_BS1_13TQ    0x0CU
#define CAN_BS1_14TQ    0x0DU
#define CAN_BS1_15TQ    0x0EU
#define CAN_BS1_16TQ    0x0FU

/* ===== Time Segment 2 ===== */

#define CAN_BS2_1TQ     0x00U
#define CAN_BS2_2TQ     0x01U
#define CAN_BS2_3TQ     0x02U
#define CAN_BS2_4TQ     0x03U
#define CAN_BS2_5TQ     0x04U
#define CAN_BS2_6TQ     0x05U
#define CAN_BS2_7TQ     0x06U
#define CAN_BS2_8TQ     0x07U

/* ===== Feature Control ===== */

#define CAN_DISABLE     0U
#define CAN_ENABLE      1U

#define CAN_MAX_FILTER_BANKS     14U
#define CAN_MAX_FILTER_NUMBERS   56U

/* ===== Filter Bank ===== */

#define CAN_FILTER_BANK_0		0U
#define CAN_FILTER_BANK_1		1U
#define CAN_FILTER_BANK_2		2U
#define CAN_FILTER_BANK_3		3U
#define CAN_FILTER_BANK_4		4U
#define CAN_FILTER_BANK_5		5U
#define CAN_FILTER_BANK_6		6U
#define CAN_FILTER_BANK_7		7U
#define CAN_FILTER_BANK_8		8U
#define CAN_FILTER_BANK_9		9U
#define CAN_FILTER_BANK_10		10U
#define CAN_FILTER_BANK_11		11U
#define CAN_FILTER_BANK_12		12U
#define CAN_FILTER_BANK_13		13U

/* ===== Filter Mode ===== */

#define CAN_FILTER_MODE_MASK     0U   // ID & Mask comparison
#define CAN_FILTER_MODE_LIST     1U   // Exact ID match

/* ===== Filter Scale ===== */

#define CAN_FILTER_SCALE_16BIT   0U
#define CAN_FILTER_SCALE_32BIT   1U

/* ===== FIFO Assignment ===== */

#define CAN_FILTER_FIFO0         0U
#define CAN_FILTER_FIFO1         1U

/* ===== Filter Activation ===== */

#define CAN_FILTER_DISABLE       0U
#define CAN_FILTER_ENABLE        1U

/* ===== Identifier Type ===== */

#define CAN_ID_STD          0U   /* Standard 11-bit ID */
#define CAN_ID_EXT          1U   /* Extended 29-bit ID */

/* ===== Frame Type ===== */

#define CAN_RTR_DATA        0U   /* Data Frame */
#define CAN_RTR_REMOTE      1U   /* Remote Frame */


#define CAN_TX_MAILBOX0      0U
#define CAN_TX_MAILBOX1      1U
#define CAN_TX_MAILBOX2      2U
#define CAN_TX_MAILBOX_MAX   3U

/* ===== Transmit Global Time ===== */

#define CAN_TGT_DISABLE     0U
#define CAN_TGT_ENABLE      1U

/* ===== DLC Limits ===== */

#define CAN_DLC_0           0U
#define CAN_DLC_1           1U
#define CAN_DLC_2           2U
#define CAN_DLC_3           3U
#define CAN_DLC_4           4U
#define CAN_DLC_5           5U
#define CAN_DLC_6           6U
#define CAN_DLC_7           7U
#define CAN_DLC_8           8U

#define CAN_MAX_DLC         8U

/* ===== ID Limits ===== */

#define CAN_STD_ID_MAX      0x7FFU        /* 11-bit max */
#define CAN_EXT_ID_MAX      0x1FFFFFFFU   /* 29-bit max */

/* ===== FIFO Identification ===== */

#define CAN_RX_FROM_FIFO0   0U
#define CAN_RX_FROM_FIFO1   1U



/* ================= Core Control ================= */

void CAN_ClkControl(CAN_Regs_t *pCANx, uint8_t EnorDi);

CAN_Status_t CAN_Init(CAN_Handle_t *CANx);					//Any to INTIALIZATION

CAN_Status_t CAN_DeInit(CAN_Handle_t *CANx);				//Any to RESET

CAN_Status_t CAN_Start(CAN_Handle_t *CANx);					//INTIALIZATION to NORMAL

CAN_Status_t CAN_Stop(CAN_Handle_t *CANx);					//NORMAL to INITIALIZATION

CAN_Status_t CAN_RequestSleep(CAN_Handle_t *CANx);			//Any to SLEEP

CAN_Status_t CAN_WakeUp(CAN_Handle_t *CANx);				//SLEEP to NORMAL

CAN_State_t  CAN_GetState(CAN_Handle_t *CANx);


/* ================= Filter Control ================= */

CAN_Status_t CAN_ConfigFilter(CAN_Handle_t *CANx, const CAN_FilterConfig_t *pFilter);

CAN_Status_t CAN_EnableFilter(CAN_Handle_t *CANx, uint8_t filterBank);

CAN_Status_t CAN_DisableFilter(CAN_Handle_t *CANx, uint8_t filterBank);


/* ================= Transmission ================= */

CAN_Status_t CAN_AddTxMessage(CAN_Handle_t *CANx, const CAN_TxHeader_t *pHeader, const uint8_t *pData, uint8_t *pMailbox);

CAN_Status_t CAN_IsTxMessagePending(CAN_Handle_t *CANx, uint8_t mailbox);

uint8_t CAN_GetTxMailboxesFreeLevel(CAN_Handle_t *CANx);

CAN_Status_t CAN_AbortTxRequest(CAN_Handle_t *CANx, uint8_t mailbox);


/* ================= Reception ================= */

CAN_Status_t CAN_GetRxMessage(CAN_Handle_t *CANx, uint8_t fifo, CAN_RxHeader_t *pHeader, uint8_t *pData);

uint8_t CAN_GetRxFifoFillLevel(CAN_Handle_t *CANx, uint8_t fifo);

#endif /* INC_STM32F303XX_CAN_DRIVER_H_ */
