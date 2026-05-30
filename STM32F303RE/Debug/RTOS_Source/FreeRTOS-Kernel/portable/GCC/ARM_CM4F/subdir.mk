################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/%.o RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/%.su RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/%.cyclo: ../RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/%.c RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4F

clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.cyclo ./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.d ./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.o ./RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel-2f-portable-2f-GCC-2f-ARM_CM4F

