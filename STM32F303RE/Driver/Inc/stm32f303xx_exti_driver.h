/*
 * stm32f303xx_exti_driver.h
 *
 *  Created on: Dec 28, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_EXTI_DRIVER_H_
#define INC_STM32F303XX_EXTI_DRIVER_H_


#include "stm32f303xx.h"

/* ================= EXTI Line Numbers ================= */

/* GPIO EXTI lines */
#define EXTI_LINE_0      0
#define EXTI_LINE_1      1
#define EXTI_LINE_2      2
#define EXTI_LINE_3      3
#define EXTI_LINE_4      4
#define EXTI_LINE_5      5
#define EXTI_LINE_6      6
#define EXTI_LINE_7      7
#define EXTI_LINE_8      8
#define EXTI_LINE_9      9
#define EXTI_LINE_10     10
#define EXTI_LINE_11     11
#define EXTI_LINE_12     12
#define EXTI_LINE_13     13
#define EXTI_LINE_14     14
#define EXTI_LINE_15     15

/* Internal peripheral EXTI lines */
#define EXTI_LINE_16     16   /* PVD */
#define EXTI_LINE_17     17   /* RTC Alarm */
#define EXTI_LINE_18     18   /* USB Wakeup */
#define EXTI_LINE_19     19   /* RTC Tamper / Timestamp */
#define EXTI_LINE_20     20   /* RTC Wakeup */
#define EXTI_LINE_21     21   /* COMP */
#define EXTI_LINE_22     22   /* COMP */
#define EXTI_LINE_23     23   /* COMP */

#define EXTI_LINE_29     29   /* COMP */
#define EXTI_LINE_30     30   /* COMP */
#define EXTI_LINE_31     31   /* COMP */

/* Lines in EXTI_IMR2 */
#define EXTI_LINE_32     32
#define EXTI_LINE_33     33
#define EXTI_LINE_34     34
#define EXTI_LINE_35     35


/* ================= EXTI Trigger Types ================= */

#define EXTI_TRIGGER_RISING        			0
#define EXTI_TRIGGER_FALLING       			1
#define EXTI_TRIGGER_RISING_FALLING 		2


/* ================= GPIO Port Codes for EXTI ================= */
/* Used in SYSCFG_EXTICR registers */

#define GPIO_PORT_A     0
#define GPIO_PORT_B     1
#define GPIO_PORT_C     2
#define GPIO_PORT_D     3
#define GPIO_PORT_E     4
#define GPIO_PORT_F     5
#define GPIO_PORT_G     6
#define GPIO_PORT_H     7


/* ================= EXTI Line Configuration ================= */

/* Configure GPIO port for EXTI line (EXTI0–EXTI15) */
void EXTI_ConfigGPIO(uint8_t exti_line, uint8_t gpio_port);

/* Configure trigger type: rising, falling, or both */
void EXTI_ConfigTrigger(uint8_t exti_line, uint8_t trigger);


/* ================= Interrupt Control ================= */

/* Enable interrupt generation for EXTI line */
void EXTI_EnableInterrupt(uint8_t exti_line);

/* Disable interrupt generation for EXTI line */
void EXTI_DisableInterrupt(uint8_t exti_line);


/* ================= Event Control (Optional) ================= */

/* Enable event generation for EXTI line */
void EXTI_EnableEvent(uint8_t exti_line);

/* Disable event generation for EXTI line */
void EXTI_DisableEvent(uint8_t exti_line);


/* ================= Pending Flag Handling ================= */

/* Clear EXTI pending flag (write 1 to clear) */
void EXTI_ClearPending(uint8_t exti_line);

/* Get EXTI pending status (returns 0 or 1) */
uint8_t EXTI_GetPending(uint8_t exti_line);


/* ================= Software Trigger ================= */

/* Generate EXTI interrupt/event by software */
void EXTI_GenerateSWInterrupt(uint8_t exti_line);


/* ================= IRQ Handling Support ================= */

/* Generic EXTI IRQ handler helper (used inside ISR) */
void EXTI_HandleIRQ(uint8_t exti_line);

/* Weak user callback called from EXTI_HandleIRQ */
void EXTI_Callback(uint8_t exti_line);


#endif /* INC_STM32F303XX_EXTI_DRIVER_H_ */
