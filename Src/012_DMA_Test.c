/*
 * 012_DMA_Test.c
 *
 *  Created on: May 19, 2026
 *      Author: aswin
 */

#include "stm32f303xx.h"
//DMA Mem2Mem Test



int main(void)
{
    DMA_Handle_t hdma;

    /* Source and destination buffers */
    uint32_t src[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    uint32_t dst[8] = {0};

    /* DMA handle configuration */
    hdma.pDMAx = DMA1;
    hdma.channelNumber = 0;   /* DMA Channel 1 (0-based index) */

    hdma.DMA_Config.Direction          = DMA_DIR_PERIPH_TO_MEM;
    hdma.DMA_Config.CircularMode       = DMA_CIRCULAR_DISABLE;
    hdma.DMA_Config.PeripheralInc      = DMA_PINC_ENABLE;
    hdma.DMA_Config.MemoryInc          = DMA_MINC_ENABLE;
    hdma.DMA_Config.PeripheralDataSize = DMA_PDATAALIGN_WORD;
    hdma.DMA_Config.MemoryDataSize     = DMA_MDATAALIGN_WORD;
    hdma.DMA_Config.Priority           = DMA_PRIORITY_HIGH;
    hdma.DMA_Config.Mem2Mem            = DMA_MEM2MEM_ENABLE;
    hdma.DMA_Config.TCInterrupt        = DMA_TCIE_DISABLE;
    hdma.DMA_Config.HTInterrupt        = DMA_HTIE_DISABLE;
    hdma.DMA_Config.TEInterrupt        = DMA_TEIE_DISABLE;

    /* Enable DMA clock */
    DMA_PeriClockControl(DMA1, ENABLE);

    /* Initialize DMA */
    DMA_Init(&hdma);

    /* Start memory-to-memory transfer */
    DMA_Start(&hdma,
              (uint32_t)src,
              (uint32_t)dst,
              8);

    /* Wait until transfer completes */
    while (DMA_GetRemainingData(&hdma) != 0U);

    /* Optional verification */
    for (uint8_t i = 0; i < 8; i++)
    {
        if (src[i] != dst[i])
        {
            /* Transfer failed */
            while (1)
            {
            }
        }
    }

    /* Transfer successful */
    while (1)
    {
    }
}
