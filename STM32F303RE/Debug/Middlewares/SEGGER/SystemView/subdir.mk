################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.c \
../Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.c \
../Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.o \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.o \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.d \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.d \
./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SEGGER/SystemView/%.o Middlewares/SEGGER/SystemView/%.su Middlewares/SEGGER/SystemView/%.cyclo: ../Middlewares/SEGGER/SystemView/%.c Middlewares/SEGGER/SystemView/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-SEGGER-2f-SystemView

clean-Middlewares-2f-SEGGER-2f-SystemView:
	-$(RM) ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.cyclo ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.d ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.o ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW.su ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.d ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.o ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_Config_FreeRTOS.su ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.cyclo ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.d ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.o ./Middlewares/SEGGER/SystemView/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-Middlewares-2f-SEGGER-2f-SystemView

