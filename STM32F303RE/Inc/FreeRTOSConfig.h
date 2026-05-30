#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/*-----------------------------------------------------------
 * Hardware configuration
 *----------------------------------------------------------*/
/* Use the ACTUAL CPU clock, not the max supported clock */

#define configCPU_CLOCK_HZ            ( 8000000UL )
#define configTICK_RATE_HZ            ( 1000U )             /* 1 ms tick */

/*-----------------------------------------------------------
 * Scheduler configuration
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION          1
#define configUSE_TIME_SLICING        1
#define configMAX_PRIORITIES          5
#define configMINIMAL_STACK_SIZE      128
#define configMAX_TASK_NAME_LEN       16
#define configIDLE_SHOULD_YIELD       1

#define configTICK_TYPE_WIDTH_IN_BITS TICK_TYPE_WIDTH_32_BITS

/*-----------------------------------------------------------
 * Memory allocation (heap_4.c)
 *----------------------------------------------------------*/
#define configSUPPORT_DYNAMIC_ALLOCATION  1
#define configSUPPORT_STATIC_ALLOCATION   0
#define configTOTAL_HEAP_SIZE             ( 12 * 1024 )
#define configAPPLICATION_ALLOCATED_HEAP  0

/*-----------------------------------------------------------
 * Cortex-M interrupt priority configuration
 *----------------------------------------------------------*/
/* STM32 uses 4 priority bits */
#define configPRIO_BITS                         4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/*-----------------------------------------------------------
 * Hook functions and diagnostics
 *----------------------------------------------------------*/
#define configCHECK_FOR_STACK_OVERFLOW    0
#define configUSE_MALLOC_FAILED_HOOK      0
#define configUSE_IDLE_HOOK               0
#define configUSE_TICK_HOOK               0

/*-----------------------------------------------------------
 * API function inclusion
 *----------------------------------------------------------*/
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_xTaskGetSchedulerState        1
#define INCLUDE_uxTaskGetStackHighWaterMark   1
#define INCLUDE_xTaskGetCurrentTaskHandle     1

/* Map FreeRTOS handlers to CMSIS names */
#define vPortSVCHandler      SVC_Handler
#define xPortPendSVHandler   PendSV_Handler
#define xPortSysTickHandler  SysTick_Handler

//Jlink
#define configUSE_TRACE_FACILITY               1
#define configUSE_STATS_FORMATTING_FUNCTIONS   1
#define INCLUDE_xTaskGetIdleTaskHandle         1

#include "SEGGER_SYSVIEW_FreeRTOS.h"

#endif /* FREERTOS_CONFIG_H */
