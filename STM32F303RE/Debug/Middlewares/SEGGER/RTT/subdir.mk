################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/SEGGER/RTT/SEGGER_RTT.c \
../Middlewares/SEGGER/RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../Middlewares/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Middlewares/SEGGER/RTT/SEGGER_RTT.o \
./Middlewares/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.o \
./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./Middlewares/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Middlewares/SEGGER/RTT/SEGGER_RTT.d \
./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SEGGER/RTT/%.o Middlewares/SEGGER/RTT/%.su Middlewares/SEGGER/RTT/%.cyclo: ../Middlewares/SEGGER/RTT/%.c Middlewares/SEGGER/RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/SEGGER/RTT/%.o: ../Middlewares/SEGGER/RTT/%.S Middlewares/SEGGER/RTT/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -u _printf_float -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Middlewares-2f-SEGGER-2f-RTT

clean-Middlewares-2f-SEGGER-2f-RTT:
	-$(RM) ./Middlewares/SEGGER/RTT/SEGGER_RTT.cyclo ./Middlewares/SEGGER/RTT/SEGGER_RTT.d ./Middlewares/SEGGER/RTT/SEGGER_RTT.o ./Middlewares/SEGGER/RTT/SEGGER_RTT.su ./Middlewares/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.d ./Middlewares/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.o ./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.cyclo ./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.d ./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.o ./Middlewares/SEGGER/RTT/SEGGER_RTT_printf.su

.PHONY: clean-Middlewares-2f-SEGGER-2f-RTT

