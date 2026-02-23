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
    uint8_t  FilterBank;
    uint8_t  FilterMode;       // Mask or List
    uint8_t  FilterScale;      // 16-bit or 32-bit
    uint32_t FilterID;
    uint32_t FilterMask;
    uint8_t  FIFOAssignment;
    uint8_t  Activation;

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
    uint32_t TimeStamp;
    uint32_t FMI;

} CAN_RxHeader_t;



typedef struct{

	CAN_Regs_t *pCANx;
	CAN_Config_t CAN_Config;
	CAN_FilterConfig_t CAN_FilterConfig;
	CAN_TxHeader_t CAN_TxMsg;
	CAN_RxHeader_t CAN_RxMsg;

}CAN_Handle_t;



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

#define CAN_MAX_FILTER_BANKS     28U

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



#endif /* INC_STM32F303XX_CAN_DRIVER_H_ */
