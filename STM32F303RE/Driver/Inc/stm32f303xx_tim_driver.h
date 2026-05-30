/*
 * stm32f303xx_tim_driver.h
 *
 *  Created on: Dec 23, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_TIM_DRIVER_H_
#define INC_STM32F303XX_TIM_DRIVER_H_


#include "stm32f303xx.h"


typedef struct{

    uint32_t GP1TIM_Prescaler;        /* PSC value */
    uint32_t GP1TIM_AutoReload;       /* ARR value */
    uint32_t GP1TIM_CounterMode;      /* Up &| Down */
    uint32_t GP1TIM_ClockDivision;    /* CKD */

}GP1_TIM_Config_t;


typedef struct{

	uint32_t GP1TIM_ICPolarity;
	uint32_t GP1TIM_ICSelection;
	uint32_t GP1TIM_ICPrescaler;
	uint32_t GP1TIM_ICFilter;

}GP1_TIM_IC_Config_t;


typedef struct
{
	uint32_t  GP1TIM_OCMode;
    uint32_t  GP1TIM_OCPolarity;
    uint32_t  GP1TIM_Compare;

}GP1_TIM_OC_Config_t;


typedef struct
{
	/* Note:
	 * - GP1TIM_Duty represents the raw CCR (Capture/Compare Register) value.
	 * - It is NOT a percentage.
	 * - PWM duty cycle is derived as:
	 *
	 *      Duty (%) = (CCR / ARR) * 100
	 *
	 * - ARR must be configured separately using the timer base initialization.
	 */
    uint32_t GP1TIM_PWMMode;     // PWM1 or PWM2
    uint32_t GP1TIM_Duty;        // CCR value
    uint32_t GP1TIM_Polarity;    // HIGH / LOW
} GP1_TIM_PWM_Config_t;



typedef struct{

	GP1_TIM_Regs_t *pGP1TIMx;
	GP1_TIM_Config_t GP1_TIM_Config;
	GP1_TIM_IC_Config_t GP1_TIM_IC_Config;
	GP1_TIM_OC_Config_t GP1_TIM_OC_Config;
	GP1_TIM_PWM_Config_t GP1_TIM_PWM_Config;
    uint32_t Channel;            /* Active channel */
    uint8_t  State;              /* RESET / READY / BUSY */

}GP1_TIM_Handle_t;


#define GP1TIM_OCMODE_FROZEN   			 	0
#define GP1TIM_OCMODE_ACTIVE   				1
#define GP1TIM_OCMODE_INACTIVE 				2
#define GP1TIM_OCMODE_TOGGLE   				3
#define GP1TIM_OCMODE_PWM1     				6
#define GP1TIM_OCMODE_PWM2     				7


#define GP1TIM_OCPOLARITY_HIGH				0
#define GP1TIM_OCPOLARITY_LOW				1

#define GP1TIM_POLARITY_HIGH				GP1TIM_OCPOLARITY_HIGH
#define GP1TIM_POLARITY_LOW					GP1TIM_OCPOLARITY_LOW

#define GP1TIM_PWMMODE_PWM1					GP1TIM_OCMODE_PWM1
#define GP1TIM_PWMMODE_PWM2					GP1TIM_OCMODE_PWM2

#define GP1TIM_CKD_1						0
#define GP1TIM_CKD_2						1
#define GP1TIM_CKD_4						2

#define GP1TIM_COUNTMODE_UP            		0  /* DIR = 0 */
#define GP1TIM_COUNTMODE_DOWN          		1  /* DIR = 1 */
#define GP1TIM_COUNTMODE_CENTER_ALIGNED 	2  /* CMS != 00 */

#define GP1TIM_STATE_RST					0
#define GP1TIM_STATE_RDY					1
#define GP1TIM_STATE_BSY					2

#define GP1_TIM_CHANNEL_1   				1
#define GP1_TIM_CHANNEL_2  					2
#define GP1_TIM_CHANNEL_3   				3
#define GP1_TIM_CHANNEL_4   				4

#define GP1_TIM_IC_POLARITY_RISING     		0   /* CCxP = 0, CCxNP = 0 */
#define GP1_TIM_IC_POLARITY_FALLING    		1   /* CCxP = 1, CCxNP = 0 */
#define GP1_TIM_IC_POLARITY_BOTHEDGE   		2   /* CCxP = 1, CCxNP = 1 */

#define GP1_TIM_IC_SELECTION_TI1   			1   /* CCxS = 01 */
#define GP1_TIM_IC_SELECTION_TI2   			2   /* CCxS = 10 */
#define GP1_TIM_IC_SELECTION_TRC   			3   /* CCxS = 11 */

#define GP1_TIM_IC_PSC_DIV1   				0   /* Capture every edge */
#define GP1_TIM_IC_PSC_DIV2   				1   /* Capture every 2nd edge */
#define GP1_TIM_IC_PSC_DIV4   				2   /* Capture every 4th edge */
#define GP1_TIM_IC_PSC_DIV8   				3   /* Capture every 8th edge */

#define GP1_TIM_IC_FILTER_NONE   			0x00U
#define GP1_TIM_IC_FILTER_1      			0x01U
#define GP1_TIM_IC_FILTER_2      			0x02U
#define GP1_TIM_IC_FILTER_3      			0x03U
#define GP1_TIM_IC_FILTER_4      			0x04U
#define GP1_TIM_IC_FILTER_5      			0x05U
#define GP1_TIM_IC_FILTER_6      			0x06U
#define GP1_TIM_IC_FILTER_7      			0x07U
#define GP1_TIM_IC_FILTER_8      			0x08U
#define GP1_TIM_IC_FILTER_9      			0x09U
#define GP1_TIM_IC_FILTER_10     			0x0AU
#define GP1_TIM_IC_FILTER_11     			0x0BU
#define GP1_TIM_IC_FILTER_12     			0x0CU
#define GP1_TIM_IC_FILTER_13     			0x0DU
#define GP1_TIM_IC_FILTER_14     			0x0EU
#define GP1_TIM_IC_FILTER_15     			0x0FU




/* Clock control */
void GP1TIM_PeriClockControl(GP1_TIM_Regs_t *pTIMx, uint8_t EnorDi);

/* Base timer */
void GP1TIM_Init(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_DeInit(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_Start(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_Stop(GP1_TIM_Handle_t *pTIMHandle);
uint32_t GP1TIM_GetCounterValue(GP1_TIM_Handle_t *pTIMHandle);


/* Delay services */
void GP1TIM_Delay_ms(GP1_TIM_Handle_t *pTIMHandle, uint32_t delay_ms);
void GP1TIM_Delay_us(GP1_TIM_Handle_t *pTIMHandle, uint32_t delay_us);

/* Output Compare */
void GP1TIM_OC_Init(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_OC_Start(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_OC_Stop(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_OC_SetCompare(GP1_TIM_Handle_t *pTIMHandle, uint32_t Compare);

/* PWM */
void GP1TIM_PWM_Init(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_PWM_Start(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_PWM_Stop(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_PWM_SetDuty(GP1_TIM_Handle_t *pTIMHandle, uint32_t Duty);

/* Input Capture */
void GP1TIM_IC_Init(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_IC_Start(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_IC_Stop(GP1_TIM_Handle_t *pTIMHandle);
uint32_t GP1TIM_IC_GetCaptureValue(GP1_TIM_Handle_t *pTIMHandle);
uint8_t GP1TIM_IC_IsCaptureFlagSet(GP1_TIM_Handle_t *pTIMHandle);
void GP1TIM_IC_ClearCaptureFlag(GP1_TIM_Handle_t *pTIMHandle);



#endif /* INC_STM32F303XX_TIM_DRIVER_H_ */
