#include "stm32f303xx.h"
#include <stdio.h>
#include <string.h>

void vApplicationStackOverflowHook(void)			//Just for RTOS
{
    while (1);
}

/* ---------------- TRIG ---------------- */
void Ultrasonic_Trigger(GP1_TIM_Handle_t *pTIM)
{
    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET);
    GP1TIM_Delay_us(pTIM, 2);

    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_SET);
    GP1TIM_Delay_us(pTIM, 10);

    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET);
}

/* ---------------- DISTANCE ---------------- */
float Ultrasonic_GetDistance(GP1_TIM_Handle_t *pTIM)
{
    uint32_t t1, t2;
    uint32_t timeout = 30000;

    /* wait for echo HIGH */
    while (!GPIO_ReadPin(GPIOA, GPIO_PIN1))
        if (--timeout == 0) return -1;

    t1 = GP1TIM_GetCounterValue(pTIM);

    /* wait for echo LOW */
    timeout = 30000;
    while (GPIO_ReadPin(GPIOA, GPIO_PIN1))
        if (--timeout == 0) return -1;

    t2 = GP1TIM_GetCounterValue(pTIM);

    uint32_t pulse;
    if (t2 >= t1)
        pulse = t2 - t1;
    else
        pulse = (0xFFFF - t1) + t2 + 1;

    return (pulse * 0.0343f) / 2.0f;   // cm
}

/* ---------------- MAIN ---------------- */
int main(void)
{
    GPIOA_REG_RST();
    USART1_REG_RST();
    TIM2_REG_RST();

    GPIO_ClkControl(GPIOA, ENABLE);

    /* TRIG PA4 */
    GPIO_Handle_t trig;
    trig.pGPIOx = GPIOA;
    trig.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN4;
    trig.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    trig.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    trig.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    trig.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&trig);

    /* ECHO PA1 */
    GPIO_Handle_t echo;
    echo.pGPIOx = GPIOA;
    echo.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN1;
    echo.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    echo.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    echo.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&echo);

    /* USART1 TX PA9 */
    GPIO_Handle_t tx;
    tx.pGPIOx = GPIOA;
    tx.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN9;
    tx.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    tx.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF7;
    tx.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    tx.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    tx.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_Init(&tx);

    USART_Handle_t usart;
    usart.pUSARTx = USART1;
    usart.USART_Config.USART_Baud = USART_BAUD_115200;
    usart.USART_Config.USART_Mode = USART_MODE_TX_ONLY;
    usart.USART_Config.USART_StopBits = USART_STOPBITS_1;
    usart.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    usart.USART_Config.USART_ParityControl = USART_PARITYCTRL_DIS;
    usart.USART_Config.USART_HWFlowControl = USART_FLOWCTRL_DIS;
    USART_Init(&usart);

    /* TIM2 → 1µs */
    GP1_TIM_Handle_t tim;
    tim.pGP1TIMx = TIM2;
    tim.Channel = GP1_TIM_CHANNEL_1;
    tim.GP1_TIM_Config.GP1TIM_Prescaler = 7;   // 8MHz → 1MHz
    tim.GP1_TIM_Config.GP1TIM_AutoReload = 0xFFFF;
    tim.GP1_TIM_Config.GP1TIM_CounterMode = GP1TIM_COUNTMODE_UP;
    tim.GP1_TIM_Config.GP1TIM_ClockDivision = GP1TIM_CKD_1;
    GP1TIM_Init(&tim);
    GP1TIM_Start(&tim);

    char buf[32];

    while (1)
    {
        Ultrasonic_Trigger(&tim);
        float d = Ultrasonic_GetDistance(&tim);

        if (d < 0)
            USART_SendData(&usart, (uint8_t*)"ERR\r\n", 5);
        else
        {
            int cm = (int)d;
            sprintf(buf, "D=%d cm\r\n", cm);
            USART_SendData(&usart, (uint8_t*)buf, strlen(buf));
        }

        GP1TIM_Delay_ms(&tim, 500);
    }
}
