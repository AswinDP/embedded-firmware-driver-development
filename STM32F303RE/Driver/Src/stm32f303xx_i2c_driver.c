/*
 * stm32f303xx_i2c_driver.c
 *
 *  Created on: Dec 14, 2025
 *      Author: aswin
 */


#include "stm32f303xx.h"


void I2C_ClkControl(I2C_Regs_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_CLK_EN();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_CLK_EN();
		}
		else if(pI2Cx == I2C3)
		{
			I2C3_CLK_EN();
		}
	}

	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_CLK_DI();
		}
		else if(pI2Cx == I2C2)
		{
			I2C2_CLK_DI();
		}
		else if(pI2Cx == I2C3)
		{
			I2C3_CLK_DI();
		}
	}
}


void I2C_Init(I2C_Handle_t *pI2CHandle)
{

	//Peripheral Clock Enable
	I2C_ClkControl(pI2CHandle->pI2Cx, ENABLE);

	// Disable I2C before configuration
	pI2CHandle->pI2Cx->CR1 &= ~(1 << 0);

    /* -------- CR1 CONFIG -------- */
    uint32_t cr1 = pI2CHandle->pI2Cx->CR1;

    cr1 &= ~(1 << 12);
    cr1 |= (pI2CHandle->I2C_Config.I2C_AnalogFilter << 12);

    cr1 &= ~(0xF << 8);
    cr1 |= (pI2CHandle->I2C_Config.I2C_DigitalFilter << 8);

    cr1 &= ~(1 << 17);
    cr1 |= (pI2CHandle->I2C_Config.I2C_NoStretch << 17);

    pI2CHandle->pI2Cx->CR1 = cr1;

	//TIMINGR Config
	// TIMINGR precomputed for APB1 = 8 MHz
	pI2CHandle->pI2Cx->TIMINGR = 0;
	uint32_t temp2 = 0;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed == 0)			    //SCL 10kHz
	{
		temp2 |= (0x1 << 28);
		temp2 |= (0x4 << 20);
		temp2 |= (0x2 << 16);
		temp2 |= (0xC3 << 8);
		temp2 |= (0xC7 << 0);
	}
	else if(pI2CHandle->I2C_Config.I2C_SCLSpeed == 1)			//SCL 100kHz
	{
		temp2 |= (0x1 << 28);
		temp2 |= (0x4 << 20);
		temp2 |= (0x2 << 16);
		temp2 |= (0xF << 8);
		temp2 |= (0x13 << 0);
	}
	else if(pI2CHandle->I2C_Config.I2C_SCLSpeed == 2)			//SCL 400kHz
	{
		temp2 |= (0x0 << 28);
		temp2 |= (0x3 << 20);
		temp2 |= (0x1 << 16);
		temp2 |= (0x3 << 8);
		temp2 |= (0x9 << 0);
	}
	else if(pI2CHandle->I2C_Config.I2C_SCLSpeed == 3)			//SCL 500kHz
	{
		temp2 |= (0x0 << 28);
		temp2 |= (0x1 << 20);
		temp2 |= (0x0 << 16);
		temp2 |= (0x3 << 8);
		temp2 |= (0x6 << 0);
	}

	pI2CHandle->pI2Cx->TIMINGR = temp2;

	// Slave Init (OA1, 7-bit)
    /* -------- OAR1 -------- */
    uint32_t oar1 = 0;
    oar1 |= ((pI2CHandle->I2C_Config.I2C_DeviceAddress & 0x7F) << 1);
    oar1 |= (1 << 15);   // OA1EN
    pI2CHandle->pI2Cx->OAR1 = oar1;

    /* -------- ENABLE I2C -------- */
    pI2CHandle->pI2Cx->CR1 |= (1 << 0);

}


void I2C_DeInit(I2C_Regs_t *pI2Cx)
{
    if (pI2Cx == I2C1)
    {
        I2C1_REG_RST();
    }
    else if (pI2Cx == I2C2)
    {
       I2C2_REG_RST();
    }
    else if (pI2Cx == I2C3)
    {
       I2C3_REG_RST();
    }
}



void I2C_SlaveSendData(I2C_Regs_t *pI2Cx, uint8_t data)
{
    /* 1. Wait until address matched */
    while (!(pI2Cx->ISR & (1 << 3)));   // ADDR

    /* 2. Clear ADDR */
    pI2Cx->ICR |= (1 << 3);             // ADDRCF

    /* 3. Wait until TXDR empty */
    while (!(pI2Cx->ISR & (1 << 1)));   // TXIS

    /* 4. Send data */
    pI2Cx->TXDR = data;

    /* 5. Wait for STOP or NACK */
    while (!(pI2Cx->ISR & ((1 << 5) | (1 << 4))));

    /* 6. Clear flags */
    if (pI2Cx->ISR & (1 << 5))
        pI2Cx->ICR |= (1 << 5);         // STOPCF

    if (pI2Cx->ISR & (1 << 4))
        pI2Cx->ICR |= (1 << 4);         // NACKCF
}



uint8_t I2C_SlaveReceiveData(I2C_Regs_t *pI2Cx)
{
    uint8_t data;

    /* 1. Wait until address matched */
    while (!(pI2Cx->ISR & (1 << 3)));   // ADDR

    /* 2. Clear ADDR */
    pI2Cx->ICR |= (1 << 3);             // ADDRCF

    /* 3. Wait for data */
    while (!(pI2Cx->ISR & (1 << 2)));   // RXNE

    /* 4. Read data */
    data = (uint8_t)pI2Cx->RXDR;

    /* 5. Wait for STOP */
    while (!(pI2Cx->ISR & (1 << 5)));   // STOPF

    /* 6. Clear STOP */
    pI2Cx->ICR |= (1 << 5);             // STOPCF

    return data;
}



void I2C_MasterSendData(I2C_Regs_t *pI2Cx,
                        uint8_t *pTxBuffer,
                        uint32_t Len,
                        uint8_t SlaveAddr)
{
    /* 1. Wait until bus is free */
    while (pI2Cx->ISR & (1 << 15))
    {
        /* wait */
    }

    /* 2. Clear old flags */
    pI2Cx->ICR |= (1<<5)|(1<<4)|(1<<8)|(1<<9);

    /* 3. Configure transfer */
    pI2Cx->CR2 = 0;
    pI2Cx->CR2 |= (SlaveAddr << 1);
    pI2Cx->CR2 |= ((Len & 0xFF) << 16);  // NBYTES
    pI2Cx->CR2 &= ~(1 << 10);             // Write
    pI2Cx->CR2 |= (1 << 13);              // START

    /* 4. Send data */
    while (Len > 0)
    {
        while (!(pI2Cx->ISR & (1 << 1)))  // TXIS
        {
            if (pI2Cx->ISR & (1 << 4))    // NACKF
            {
                pI2Cx->CR2 |= (1 << 14);  // STOP

                while (!(pI2Cx->ISR & (1 << 5))); // STOPF
                pI2Cx->ICR |= (1 << 5);           // STOPCF
                pI2Cx->ICR |= (1 << 4);           // NACKCF
                return;
            }
        }

        pI2Cx->TXDR = *pTxBuffer++;
        Len--;
    }

    /* 5. Wait for transfer complete */
    while (!(pI2Cx->ISR & (1 << 6)));     // TC

    /* 6. Generate STOP */
    pI2Cx->CR2 |= (1 << 14);

    /* 7. Wait for STOP and clear */
    while (!(pI2Cx->ISR & (1 << 5)));     // STOPF
    pI2Cx->ICR |= (1 << 5);
}




void I2C_MasterReceiveData(I2C_Regs_t *pI2Cx,
                           uint8_t *pRxBuffer,
                           uint32_t Len,
                           uint8_t SlaveAddr)
{
    /* 1. Wait until bus is free */
    while (pI2Cx->ISR & (1 << 15))
    {
        /* wait */
    }

    /* 2. Clear flags */
    pI2Cx->ICR |= (1<<5)|(1<<4)|(1<<8)|(1<<9);

    /* 3. Configure transfer */
    pI2Cx->CR2 = 0;
    pI2Cx->CR2 |= (SlaveAddr << 1);
    pI2Cx->CR2 |= ((Len & 0xFF) << 16);   // NBYTES
    pI2Cx->CR2 |= (1 << 10);              // RD_WRN
    pI2Cx->CR2 |= (1 << 13);              // START

    /* 4. Receive data */
    while (Len > 0)
    {
        while (!(pI2Cx->ISR & (1 << 2)))   // RXNE
        {
            /* Optional: handle errors here */
        }

        *pRxBuffer++ = (uint8_t)pI2Cx->RXDR;
        Len--;
    }

    /* 5. Wait for transfer complete */
    while (!(pI2Cx->ISR & (1 << 6)));      // TC

    /* 6. Generate STOP */
    pI2Cx->CR2 |= (1 << 14);

    /* 7. Wait for STOP and clear */
    while (!(pI2Cx->ISR & (1 << 5)));      // STOPF
    pI2Cx->ICR |= (1 << 5);
}




