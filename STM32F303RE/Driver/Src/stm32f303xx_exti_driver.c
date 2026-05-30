/*
 * stm32f303xx_exti_driver.c
 *
 *  Created on: Dec 28, 2025
 *      Author: aswin
 */


#include "stm32f303xx.h"

/* ================= EXTI Line Configuration ================= */

/* Configure GPIO port for EXTI line (EXTI0–EXTI15) */
void EXTI_ConfigGPIO(uint8_t exti_line, uint8_t gpio_port)
{
	SYSCFG_CLK_EN();

	if (exti_line > 15)
	    return;

	SYSCFG->EXTICR[exti_line / 4] &= ~(0xF << ((exti_line % 4) * 4));
	SYSCFG->EXTICR[exti_line / 4] |= ((gpio_port) << ((exti_line % 4) * 4));
}

/* Configure trigger type: rising, falling, or both */
void EXTI_ConfigTrigger(uint8_t exti_line, uint8_t trigger)
{
	if(trigger == EXTI_TRIGGER_RISING)
	{
	    if (exti_line < 32)
	    {
	        EXTI->FTSR1 &= ~(1U << exti_line);
	        EXTI->RTSR1 &= ~(1U << exti_line);
	        EXTI->RTSR1 |= (1U << exti_line);
	    }
	    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
	    {
	        EXTI->FTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->RTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->RTSR2 |= (1U << (exti_line - 32));
	    }
	    else return;
	}

	else if(trigger == EXTI_TRIGGER_FALLING)
	{
	    if (exti_line < 32)
	    {
	        EXTI->RTSR1 &= ~(1U << exti_line);
	        EXTI->FTSR1 &= ~(1U << exti_line);
	        EXTI->FTSR1 |= (1U << exti_line);
	    }
	    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
	    {
	        EXTI->RTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->FTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->FTSR2 |= (1U << (exti_line - 32));
	    }
	    else return;
	}
	else
	{
	    if (exti_line < 32)
	    {
	        EXTI->FTSR1 &= ~(1U << exti_line);
	        EXTI->RTSR1 &= ~(1U << exti_line);
	        EXTI->FTSR1 |= (1U << exti_line);
	        EXTI->RTSR1 |= (1U << exti_line);
	    }
	    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
	    {
	        EXTI->FTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->RTSR2 &= ~(1U << (exti_line - 32));
	        EXTI->FTSR2 |= (1U << (exti_line - 32));
	        EXTI->RTSR2 |= (1U << (exti_line - 32));
	    }
	    else return;
	}

}


/* ================= Interrupt Control ================= */

/* Enable interrupt generation for EXTI line */
void EXTI_EnableInterrupt(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->IMR1 |= (1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->IMR2 |= (1U << (exti_line - 32));
    }
    else return;
}


/* Disable interrupt generation for EXTI line */
void EXTI_DisableInterrupt(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->IMR1 &= ~(1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->IMR2 &= ~(1U << (exti_line - 32));
    }
    else return;
}


/* ================= Event Control (Optional) ================= */

/* Enable event generation for EXTI line */
void EXTI_EnableEvent(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->EMR1 |= (1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->EMR2 |= (1U << (exti_line - 32));
    }
    else return;
}

/* Disable event generation for EXTI line */
void EXTI_DisableEvent(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->EMR1 &= ~(1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->EMR2 &= ~(1U << (exti_line - 32));
    }
    else return;
}


/* ================= Pending Flag Handling ================= */

/* Clear EXTI pending flag (write 1 to clear) */
void EXTI_ClearPending(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->PR1 |= (1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->PR2 |= (1U << (exti_line - 32));
    }
    else return;
}

/* Get EXTI pending status (returns 0 or 1) */
uint8_t EXTI_GetPending(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        return (EXTI->PR1 >> exti_line & 1U);			//Operator precedence handles this :)
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        return (EXTI->PR2 >> (exti_line - 32) & 1U);    //Operator precedence handles this :)
    }
    else return 0;
}


/* ================= Software Trigger ================= */

/* Generate EXTI interrupt/event by software */
void EXTI_GenerateSWInterrupt(uint8_t exti_line)
{
    if (exti_line < 32)
    {
        EXTI->SWIER1 |= (1U << exti_line);
    }
    else if (exti_line < 36)   // STM32F303 supports up to EXTI35
    {
        EXTI->SWIER2 |= (1U << (exti_line - 32));
    }
    else return;
}


/* ================= IRQ Handling Support ================= */

/* Generic EXTI IRQ handler helper (used inside ISR) */
void EXTI_HandleIRQ(uint8_t exti_line)
{
    if (EXTI_GetPending(exti_line))
    {
        EXTI_ClearPending(exti_line);
        EXTI_Callback(exti_line);
    }
}


/* Weak user callback called from EXTI_HandleIRQ */
__attribute__((weak)) void EXTI_Callback(uint8_t exti_line)
{
    // empty default
}


















