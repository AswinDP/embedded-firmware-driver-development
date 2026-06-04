/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : nrf52840_gpio.c
Purpose : GPIO source file

*/

#include "nrf52840_gpio.h"



/*********************************************************************
 * GPIO_Init
 *********************************************************************/

void GPIO_Init(GPIO_PinConfig_t *pGPIOConfig)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;
    uint32_t temp = 0;

    /* Determine Port and Pin */
    pGPIOx = GPIO_GET_PORT(pGPIOConfig->GPIO_PinNo);
    pin    = GPIO_GET_PIN(pGPIOConfig->GPIO_PinNo);

    /* DIR */
    temp |= (pGPIOConfig->GPIO_PinType << 0);

    /* INPUT BUFFER */
    temp |= (pGPIOConfig->GPIO_PinInBuff << 1);

    /* PULL */
    temp |= (pGPIOConfig->GPIO_PinPuPd << 2);

    /* DRIVE */
    temp |= (pGPIOConfig->GPIO_PinDrive << 8);

    /* SENSE */
    temp |= (pGPIOConfig->GPIO_PinSense << 16);

    /* Configure pin */
    pGPIOx->PIN_CNF[pin] = temp;
}

/*********************************************************************
 * GPIO_DeInit
 *********************************************************************/

void GPIO_DeInit(uint8_t PinNo)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    pGPIOx->PIN_CNF[pin] = 0;
}

/*********************************************************************
 * GPIO_SetPin
 *********************************************************************/

void GPIO_SetPin(uint8_t PinNo)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    pGPIOx->OUTSET = (1UL << pin);
}

/*********************************************************************
 * GPIO_ClearPin
 *********************************************************************/

void GPIO_ClearPin(uint8_t PinNo)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    pGPIOx->OUTCLR = (1UL << pin);
}

/*********************************************************************
 * GPIO_WritePin
 *********************************************************************/

void GPIO_WritePin(uint8_t PinNo,
                   uint8_t Value)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    if(Value)
    {
        pGPIOx->OUTSET = (1UL << pin);
    }
    else
    {
        pGPIOx->OUTCLR = (1UL << pin);
    }
}

/*********************************************************************
 * GPIO_ReadPin
 *********************************************************************/

uint8_t GPIO_ReadPin(uint8_t PinNo)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    return (uint8_t)((pGPIOx->IN >> pin) & 0x01U);
}

/*********************************************************************
 * GPIO_TogglePin
 *********************************************************************/

void GPIO_TogglePin(uint8_t PinNo)
{
    GPIO_Reg_def_t *pGPIOx;
    uint8_t pin;

    pGPIOx = GPIO_GET_PORT(PinNo);
    pin    = GPIO_GET_PIN(PinNo);

    if(pGPIOx->OUT & (1UL << pin))
    {
        pGPIOx->OUTCLR = (1UL << pin);
    }
    else
    {
        pGPIOx->OUTSET = (1UL << pin);
    }
}








/******************************* END OF FILE *********************************/