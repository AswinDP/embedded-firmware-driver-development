/*
 * stm32f303xx_dma_driver.c
 *
 *  Created on: May 17, 2026
 *      Author: aswin
 */

#include "stm32f303xx_dma_driver.h"

/* ============================================================
 * DMA Clock Control
 * ============================================================
 */
void DMA_PeriClockControl(DMA_Regs_t *pDMAx, uint8_t EnOrDi)
{
	if(EnorDi == ENABLE)
	{
		if(pDMAx == DMA1)
		{
			DMA1_CLK_EN();
		}
	}

	else
	{
		if(pDMAx == DMA1)
		{
			DMA1_CLK_DI();
		}
	}
}


/* ============================================================
 * DMA Initialization / Deinitialization
 * ============================================================
 */
void DMA_Init(DMA_Handle_t *pDMAHandle)
{
	//Disable Channel
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR = 0;
	/*
	This disables channel and resets the register (default reset value is 0x00000000)
	This also helps to reduce if cases in future by making |= a safe operation for both 0 and 1
	*/

	/*
		Configure Channel
	*/

	//Direction
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.Direction << DMA_CCR_DIR);

	//CircularMode
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.CircularMode << DMA_CCR_CIRC);

	//Peri Inc
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.PeripheralInc << DMA_CCR_PINC);

	//Mem Inc
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.MemoryInc << DMA_CCR_MINC);

	//Peri Data Size
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.PeripheralDataSize << DMA_CCR_PSIZE);

	//Mem Data Size
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.MemoryDataSize << DMA_CCR_MSIZE);

	//Priority
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.Priority << DMA_CCR_PL);

	//Mem2Mem
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.Mem2Mem << DMA_CCR_MEM2MEM);

	//TCI
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.TCInterrupt << DMA_CCR_TCIE);

	//HTI
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.HTInterrupt << DMA_CCR_HTIE);

	//TEI
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (pDMAHandle->DMA_Config.TEInterrupt << DMA_CCR_TEIE);

	//Channel Hasn't enabled yet

}

void DMA_DeInit(DMA_Handle_t *pDMAHandle)
{
	//Clears CCR and Disables Channel
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR = 0;

	//Clears CNDTR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CNDTR = 0;

	//Clears CPAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CPAR = 0;

	//Clears CMAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CMAR = 0;

	//Clears Global Flag
	pDMAHandle->pDMAx->IFCR = (0x0FU << (pDMAHandle->channelNumber * 4));
}


/* ============================================================
 * DMA Transfer Control
 * ============================================================
 */
void DMA_Start(DMA_Handle_t *pDMAHandle, uint32_t srcAddr, uint32_t dstAddr, uint16_t len)
{
	//Disables Channel
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR &= ~(1U << DMA_CCR_EN);

	//Clears Global Flag
	pDMAHandle->pDMAx->IFCR = (0x0FU << (pDMAHandle->channelNumber * 4));

	//Load CPAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CPAR = srcAddr;

	//Load CMAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CMAR = dstAddr;

	//Set Data Length
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CNDTR = len;

	//Enable Channel
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR |= (1U << DMA_CCR_EN);
}


void DMA_Stop(DMA_Handle_t *pDMAHandle)
{
	//Disables Channel
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CCR &= ~(1U << DMA_CCR_EN);

	//Deinit clears everything completely whereas stop just disables the channel only
	//Supports Dynamic reconfiguration with existing channel configuration

	//Clears Global Flag
	pDMAHandle->pDMAx->IFCR = (0x0FU << (pDMAHandle->channelNumber * 4));
}


/* ============================================================
 * DMA Dynamic Reconfiguration
 * ============================================================
 */
void DMA_SetPeripheralAddress(DMA_Handle_t *pDMAHandle, uint32_t periphAddr)
{
	//Load CPAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CPAR = periphAddr;
}

void DMA_SetMemoryAddress(DMA_Handle_t *pDMAHandle, uint32_t memAddr)
{
	//Load CMAR
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CMAR = memAddr;
}

void DMA_SetTransferLength(DMA_Handle_t *pDMAHandle, uint16_t len)
{
	//Set Data Length
	pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CNDTR = len;
}


/* ============================================================
 * DMA Status / Monitoring
 * ============================================================
 */
uint16_t DMA_GetRemainingData(DMA_Handle_t *pDMAHandle)
{
	return ((uint16_t)pDMAHandle->pDMAx->CHANNEL[pDMAHandle->channelNumber].CNDTR);
}


































