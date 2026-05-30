################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.c 

OBJS += \
./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.o 

C_DEPS += \
./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS_Source/FreeRTOS-Kernel/portable/MemMang/%.o RTOS_Source/FreeRTOS-Kernel/portable/MemMang/%.su RTOS_Source/FreeRTOS-Kernel/portable/MemMang/%.cyclo: ../RTOS_Source/FreeRTOS-Kernel/portable/MemMang/%.c RTOS_Source/FreeRTOS-Kernel/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang

clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang:
	-$(RM) ./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.cyclo ./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.d ./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.o ./RTOS_Source/FreeRTOS-Kernel/portable/MemMang/heap_4.su

.PHONY: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang

