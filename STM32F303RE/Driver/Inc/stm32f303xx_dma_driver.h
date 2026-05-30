/*
 * stm32f303xx_dma_driver.h
 *
 *  Created on: May 17, 2026
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_DMA_DRIVER_H_
#define INC_STM32F303XX_DMA_DRIVER_H_


#include "stm32f303xx.h"

typedef struct
{
    uint8_t Direction;
    uint8_t CircularMode;
    uint8_t PeripheralInc;
    uint8_t MemoryInc;
    uint8_t PeripheralDataSize;
    uint8_t MemoryDataSize;
    uint8_t Priority;
    uint8_t Mem2Mem;
    uint8_t TCInterrupt;
    uint8_t HTInterrupt;
    uint8_t TEInterrupt;
} DMA_Config_t;


typedef struct
{
    DMA_Regs_t *pDMAx;
    uint8_t channelNumber;
    DMA_Config_t DMA_Config;
} DMA_Handle_t;




/* ============================================================
 * DMA CONFIGURATION MACROS
 * For use with DMA_Config_t
 * ============================================================
 */

/* ------------------------------------------------------------
 * Generic Enable / Disable
 * ------------------------------------------------------------
 */
#define DMA_DISABLE                    0U
#define DMA_ENABLE                     1U

/* ------------------------------------------------------------
 * Transfer Direction
 * ------------------------------------------------------------
 */
#define DMA_DIR_PERIPH_TO_MEM          0U
#define DMA_DIR_MEM_TO_PERIPH          1U

/* ------------------------------------------------------------
 * Circular Mode
 * ------------------------------------------------------------
 */
#define DMA_CIRCULAR_DISABLE           DMA_DISABLE
#define DMA_CIRCULAR_ENABLE            DMA_ENABLE

/* ------------------------------------------------------------
 * Peripheral Address Increment
 * ------------------------------------------------------------
 */
#define DMA_PINC_DISABLE               DMA_DISABLE
#define DMA_PINC_ENABLE                DMA_ENABLE

/* ------------------------------------------------------------
 * Memory Address Increment
 * ------------------------------------------------------------
 */
#define DMA_MINC_DISABLE               DMA_DISABLE
#define DMA_MINC_ENABLE                DMA_ENABLE

/* ------------------------------------------------------------
 * Peripheral Data Width
 * ------------------------------------------------------------
 */
#define DMA_PDATAALIGN_BYTE            0U
#define DMA_PDATAALIGN_HALFWORD        1U
#define DMA_PDATAALIGN_WORD            2U

/* ------------------------------------------------------------
 * Memory Data Width
 * ------------------------------------------------------------
 */
#define DMA_MDATAALIGN_BYTE            0U
#define DMA_MDATAALIGN_HALFWORD        1U
#define DMA_MDATAALIGN_WORD            2U

/* ------------------------------------------------------------
 * Channel Priority
 * ------------------------------------------------------------
 */
#define DMA_PRIORITY_LOW               0U
#define DMA_PRIORITY_MEDIUM            1U
#define DMA_PRIORITY_HIGH              2U
#define DMA_PRIORITY_VERY_HIGH         3U

/* ------------------------------------------------------------
 * Memory-to-Memory Mode
 * ------------------------------------------------------------
 */
#define DMA_MEM2MEM_DISABLE            DMA_DISABLE
#define DMA_MEM2MEM_ENABLE             DMA_ENABLE

/* ------------------------------------------------------------
 * Transfer Complete Interrupt
 * ------------------------------------------------------------
 */
#define DMA_TCIE_DISABLE               DMA_DISABLE
#define DMA_TCIE_ENABLE                DMA_ENABLE

/* ------------------------------------------------------------
 * Half Transfer Interrupt
 * ------------------------------------------------------------
 */
#define DMA_HTIE_DISABLE               DMA_DISABLE
#define DMA_HTIE_ENABLE                DMA_ENABLE

/* ------------------------------------------------------------
 * Transfer Error Interrupt
 * ------------------------------------------------------------
 */
#define DMA_TEIE_DISABLE               DMA_DISABLE
#define DMA_TEIE_ENABLE                DMA_ENABLE

/* ------------------------------------------------------------
 * Channel Number
 * ------------------------------------------------------------
 */
#define DMA_CHANNEL_1					0
#define DMA_CHANNEL_2					1
#define DMA_CHANNEL_3					2
#define DMA_CHANNEL_4					3
#define DMA_CHANNEL_5					4
#define DMA_CHANNEL_6					5
#define DMA_CHANNEL_7					6



/* ============================================================
 * DMA Clock Control
 * ============================================================
 */
void DMA_PeriClockControl(DMA_Regs_t *pDMAx, uint8_t EnOrDi);

/* ============================================================
 * DMA Initialization / Deinitialization
 * ============================================================
 */
void DMA_Init(DMA_Handle_t *pDMAHandle);

void DMA_DeInit(DMA_Handle_t *pDMAHandle);

/* ============================================================
 * DMA Transfer Control
 * ============================================================
 */
void DMA_Start(DMA_Handle_t *pDMAHandle, uint32_t srcAddr, uint32_t dstAddr, uint16_t len);

void DMA_Stop(DMA_Handle_t *pDMAHandle);

/* ============================================================
 * DMA Dynamic Reconfiguration
 * ============================================================
 */
void DMA_SetPeripheralAddress(DMA_Handle_t *pDMAHandle, uint32_t periphAddr);

void DMA_SetMemoryAddress(DMA_Handle_t *pDMAHandle, uint32_t memAddr);

void DMA_SetTransferLength(DMA_Handle_t *pDMAHandle, uint16_t len);

/* ============================================================
 * DMA Status / Monitoring
 * ============================================================
 */
uint16_t DMA_GetRemainingData(DMA_Handle_t *pDMAHandle);

uint8_t DMA_GetFlagStatus(DMA_Handle_t *pDMAHandle, uint32_t flagMask);

void DMA_ClearFlags(DMA_Handle_t *pDMAHandle);

/* ============================================================
 * DMA Interrupt Handling
 * ============================================================
 */
void DMA_IRQHandling(DMA_Handle_t *pDMAHandle);

/* ============================================================
 * DMA Callback (implemented by application)
 * ============================================================
 */
void DMA_ApplicationEventCallback(DMA_Handle_t *pDMAHandle,
                                  uint8_t event);


#endif /* INC_STM32F303XX_DMA_DRIVER_H_ */
