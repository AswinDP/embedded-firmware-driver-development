#include "FreeRTOS.h"
#include "task.h"
#include "stm32f303xx.h"
#include "SEGGER_SYSVIEW.h"

/* LED 1: Fast blink */
void LED1_Task(void *argument)
{
    while (1)
    {
    	SEGGER_SYSVIEW_PrintfHost("LED1 toggled");
        GPIO_TogglePin(GPIOC, GPIO_PIN8);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

/* LED 2: Slow blink */
void LED2_Task(void *argument)
{
    while (1)
    {
    	SEGGER_SYSVIEW_PrintfHost("LED2 toggled");
        GPIO_TogglePin(GPIOC, GPIO_PIN9);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void MY_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    uint32_t reg_val;

    reg_val  = SCB->AIRCR;
    reg_val &= ~(0xFFFF0000 | (7U << 8U));
    reg_val |= (0x05FA0000 | ((PriorityGroup & 0x7U) << 8U));

    SCB->AIRCR = reg_val;

    /* Ensure effect takes place immediately */
    __asm volatile ("dsb");
    __asm volatile ("isb");
}


int main(void)
{

	MY_NVIC_SetPriorityGrouping(3);

    GPIO_Handle_t GPIO1;
    GPIO_Handle_t GPIO2;

    /* Enable GPIOA clock */
    GPIO_ClkControl(GPIOC, ENABLE);

    /* PA2 */
    GPIO1.pGPIOx = GPIOC;
    GPIO1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN8;
    GPIO1.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;
    GPIO1.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_MEDIUM;
    GPIO1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GPIO1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    /* PA3 */
    GPIO2.pGPIOx = GPIOC;
    GPIO2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN9;
    GPIO2.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;
    GPIO2.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_MEDIUM;
    GPIO2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GPIO2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GPIO1);
    GPIO_Init(&GPIO2);


    xTaskCreate(LED1_Task, "LED1", 128, NULL, 1, NULL);
    xTaskCreate(LED2_Task, "LED2", 128, NULL, 1, NULL);


    SEGGER_SYSVIEW_Conf();

    SEGGER_SYSVIEW_Start();

    vTaskStartScheduler();

    while (1);
}
