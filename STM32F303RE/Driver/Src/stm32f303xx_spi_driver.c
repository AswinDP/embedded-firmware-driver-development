/*
 * stm32f303xx_spi_driver.c
 *
 *  Created on: Dec 10, 2025
 *      Author: aswin
 */

#include "stm32f303xx_spi_driver.h"



void SPI_ClkControl(SPI_Regs_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_CLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_CLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_CLK_EN();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_CLK_EN();
		}
	}

	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_CLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_CLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_CLK_DI();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_CLK_DI();
		}
	}
}



void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable

	SPI_ClkControl(pSPIHandle->pSPIx, ENABLE);

	//first lets configure the SPI_CR1 register

	uint32_t tempreg = 0;

	//a. Configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	//b. configure the CPOL and CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	//c. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~( 1 << 10);
		tempreg &= ~( 1 << 15);

	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg &= ~(1 << 10);   // RXONLY = 0
		tempreg |= ( 1 << 15);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_Srx)
	{
		//BIDI mode should be cleared
		tempreg &= ~( 1 << 15);
		//RXONLY bit must be set
		tempreg |= ( 1 << 10);
	}

	//d. Configure LSB
	tempreg &= ~(1 << 7);

	//e.  Configure the CRCEN
	if(pSPIHandle->SPIConfig.SPI_CRCEN == SPI_CRCDIS)
	{
		tempreg &= ~(1 << 13);
	}
	else if(pSPIHandle->SPIConfig.SPI_CRCEN == SPI_CRCEN_8BITS)
	{
		tempreg |= (1 << 13);
		tempreg &= ~(1 << 11);
	}
	else
	{
		tempreg |= (1 << 13);
		tempreg |= (1 << 11);
	}

	// f. Configure SSM and SSI
	tempreg |= (pSPIHandle->SPIConfig.SPI_SSM << 9);

	if(pSPIHandle->SPIConfig.SPI_SSM == ENABLE)
	{
	    /* Required in master mode to avoid MODF */
	    tempreg |= (1 << 8);   // SSI = 1
	}
	else
	{
	    /* Hardware NSS management */
	    tempreg &= ~(1 << 8);  // SSI = 0 (clean state)
	}

	//g. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2 ;

	pSPIHandle->pSPIx->CR1 = tempreg;


	//Next lets configure the SPI_CR2 register

	tempreg = 0;

	/* Disable SPI before configuring CR2 */
	pSPIHandle->pSPIx->CR1 &= ~(1 << 6); // SPE = 0

	/* Data size */
	tempreg |= (pSPIHandle->SPIConfig.SPI_DS << 8);

	//SSOE is not handled as of now!

	/* RX FIFO threshold */
	if(pSPIHandle->SPIConfig.SPI_DS <= SPI_DS_8BITS)
	{
	    tempreg |= (1 << 13); // FRXTH = 1
	}

	pSPIHandle->pSPIx->CR2 = tempreg;

	pSPIHandle->pSPIx->CR1 |= (1 << 6);

    pSPIHandle->TxState = SPI_READY;
    pSPIHandle->RxState = SPI_READY;

}


void SPI_DeInit(SPI_Regs_t *pSPIx)
{

}






uint8_t SPI_GetFlagStatus(SPI_Regs_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return SET;
	}
	return RESET;
}





void SPI_SendData(SPI_Regs_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{

    while(Len > 0)
    {
        /* Wait until TXE is set */
        while(SPI_GetFlagStatus(pSPIx, (1 << 1)) == RESET);

        if(((pSPIx->CR2 >> 8) & 0xF) == SPI_DS_16BITS)
        {
            /* Ensure enough data */
            if(Len < 2)
                break;

            /* Load 16-bit data */
            pSPIx->DR = *((uint16_t *)pTxBuffer);

            pTxBuffer += 2;
            Len -= 2;
        }
        else /* 8-bit */
        {
            pSPIx->DR = *pTxBuffer;
            pTxBuffer++;
            Len--;
        }
    }

    /* Wait until SPI not busy */
    while(pSPIx->SR & (1 << 7)); // BSY
}




void SPI_ReceiveData(SPI_Regs_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{

    while(Len > 0)
    {
        /* Wait until RXNE is set */
        while(SPI_GetFlagStatus(pSPIx, (1 << 0)) == RESET);

        if(((pSPIx->CR2 >> 8) & 0xF) == SPI_DS_16BITS)
        {
            /* Ensure enough space */
            if(Len < 2)
                break;

            *((uint16_t *)pRxBuffer) = (uint16_t)pSPIx->DR;

            pRxBuffer += 2;
            Len -= 2;
        }
        else /* 8-bit */
        {
            *pRxBuffer = (uint8_t)pSPIx->DR;

            pRxBuffer++;
            Len--;
        }
    }

    /* Wait until SPI not busy */
    while(pSPIx->SR & (1 << 7)); // BSY
}



uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	if(pSPIHandle->TxState != SPI_BUSY_TX)
	{
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen     = Len;
		pSPIHandle->TxState   = SPI_BUSY_TX;

		/* Enable TXE interrupt */
		pSPIHandle->pSPIx->CR2 |= (1 << 7); // TXEIE

		return 0;
	}

	return pSPIHandle->TxState;
}



uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	if(pSPIHandle->RxState != SPI_BUSY_RX)
	{
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen     = Len;
		pSPIHandle->RxState   = SPI_BUSY_RX;

		/* Enable RXNE interrupt */
		pSPIHandle->pSPIx->CR2 |= (1 << 6); // RXNEIE

		return 0;
	}

	return pSPIHandle->RxState;
}



void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint32_t temp1, temp2;

	/* Read status register and control register */
	temp1 = pHandle->pSPIx->SR;
	temp2 = pHandle->pSPIx->CR2;

	/* ---------------- TXE INTERRUPT ---------------- */
	if ((temp1 & (1 << 1)) && (temp2 & (1 << 7)))
	{
		/* TXE is set and TXEIE enabled */

		if (pHandle->TxLen > 0)
		{
			/* Send 8-bit data */
			*(volatile uint8_t *)&pHandle->pSPIx->DR =
					*(pHandle->pTxBuffer);

			pHandle->pTxBuffer++;
			pHandle->TxLen--;
		}
		else
		{
			/* Transmission complete */
			pHandle->pSPIx->CR2 &= ~(1 << 7); // Disable TXEIE
			pHandle->TxState = SPI_READY;
		}
	}

	/* ---------------- RXNE INTERRUPT ---------------- */
	if ((temp1 & (1 << 0)) && (temp2 & (1 << 6)))
	{
		/* RXNE is set and RXNEIE enabled */

		if (pHandle->RxLen > 0)
		{
			/* Receive 8-bit data */
			*(pHandle->pRxBuffer) =
					*(volatile uint8_t *)&pHandle->pSPIx->DR;

			pHandle->pRxBuffer++;
			pHandle->RxLen--;
		}
		else
		{
			/* Reception complete */
			pHandle->pSPIx->CR2 &= ~(1 << 6); // Disable RXNEIE
			pHandle->RxState = SPI_READY;
		}
	}
}



void SPI_SendReceiveData(SPI_Regs_t *pSPIx,
                         uint8_t *pTxBuffer,
                         uint8_t *pRxBuffer,
                         uint32_t len)
{
    while (len > 0)
    {
        /* 1. Wait until TX buffer empty */
        while (!(pSPIx->SR & (1 << 1)));

        /* 2. Write data (8-bit safe access) */
        *((__vo uint8_t *)&pSPIx->DR) = *pTxBuffer;
        pTxBuffer++;

        /* 3. Wait until RX buffer not empty */
        while (!(pSPIx->SR & (1 << 0)));

        /* 4. Read received data */
        *pRxBuffer = *((__vo uint8_t *)&pSPIx->DR);
        pRxBuffer++;

        len--;
    }

    /* 5. Wait until SPI not busy */
    while (pSPIx->SR & (1 << 7));
}


