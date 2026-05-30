################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS_Source/FreeRTOS-Kernel/croutine.c \
../RTOS_Source/FreeRTOS-Kernel/event_groups.c \
../RTOS_Source/FreeRTOS-Kernel/list.c \
../RTOS_Source/FreeRTOS-Kernel/queue.c \
../RTOS_Source/FreeRTOS-Kernel/stream_buffer.c \
../RTOS_Source/FreeRTOS-Kernel/tasks.c \
../RTOS_Source/FreeRTOS-Kernel/timers.c 

OBJS += \
./RTOS_Source/FreeRTOS-Kernel/croutine.o \
./RTOS_Source/FreeRTOS-Kernel/event_groups.o \
./RTOS_Source/FreeRTOS-Kernel/list.o \
./RTOS_Source/FreeRTOS-Kernel/queue.o \
./RTOS_Source/FreeRTOS-Kernel/stream_buffer.o \
./RTOS_Source/FreeRTOS-Kernel/tasks.o \
./RTOS_Source/FreeRTOS-Kernel/timers.o 

C_DEPS += \
./RTOS_Source/FreeRTOS-Kernel/croutine.d \
./RTOS_Source/FreeRTOS-Kernel/event_groups.d \
./RTOS_Source/FreeRTOS-Kernel/list.d \
./RTOS_Source/FreeRTOS-Kernel/queue.d \
./RTOS_Source/FreeRTOS-Kernel/stream_buffer.d \
./RTOS_Source/FreeRTOS-Kernel/tasks.d \
./RTOS_Source/FreeRTOS-Kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS_Source/FreeRTOS-Kernel/%.o RTOS_Source/FreeRTOS-Kernel/%.su RTOS_Source/FreeRTOS-Kernel/%.cyclo: ../RTOS_Source/FreeRTOS-Kernel/%.c RTOS_Source/FreeRTOS-Kernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel

clean-RTOS_Source-2f-FreeRTOS-2d-Kernel:
	-$(RM) ./RTOS_Source/FreeRTOS-Kernel/croutine.cyclo ./RTOS_Source/FreeRTOS-Kernel/croutine.d ./RTOS_Source/FreeRTOS-Kernel/croutine.o ./RTOS_Source/FreeRTOS-Kernel/croutine.su ./RTOS_Source/FreeRTOS-Kernel/event_groups.cyclo ./RTOS_Source/FreeRTOS-Kernel/event_groups.d ./RTOS_Source/FreeRTOS-Kernel/event_groups.o ./RTOS_Source/FreeRTOS-Kernel/event_groups.su ./RTOS_Source/FreeRTOS-Kernel/list.cyclo ./RTOS_Source/FreeRTOS-Kernel/list.d ./RTOS_Source/FreeRTOS-Kernel/list.o ./RTOS_Source/FreeRTOS-Kernel/list.su ./RTOS_Source/FreeRTOS-Kernel/queue.cyclo ./RTOS_Source/FreeRTOS-Kernel/queue.d ./RTOS_Source/FreeRTOS-Kernel/queue.o ./RTOS_Source/FreeRTOS-Kernel/queue.su ./RTOS_Source/FreeRTOS-Kernel/stream_buffer.cyclo ./RTOS_Source/FreeRTOS-Kernel/stream_buffer.d ./RTOS_Source/FreeRTOS-Kernel/stream_buffer.o ./RTOS_Source/FreeRTOS-Kernel/stream_buffer.su ./RTOS_Source/FreeRTOS-Kernel/tasks.cyclo ./RTOS_Source/FreeRTOS-Kernel/tasks.d ./RTOS_Source/FreeRTOS-Kernel/tasks.o ./RTOS_Source/FreeRTOS-Kernel/tasks.su ./RTOS_Source/FreeRTOS-Kernel/timers.cyclo ./RTOS_Source/FreeRTOS-Kernel/timers.d ./RTOS_Source/FreeRTOS-Kernel/timers.o ./RTOS_Source/FreeRTOS-Kernel/timers.su

.PHONY: clean-RTOS_Source-2f-FreeRTOS-2d-Kernel

