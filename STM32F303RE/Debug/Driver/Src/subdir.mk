################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/stm32f303xx_can_driver.c \
../Driver/Src/stm32f303xx_dma_driver.c \
../Driver/Src/stm32f303xx_exti_driver.c \
../Driver/Src/stm32f303xx_gpio_driver.c \
../Driver/Src/stm32f303xx_i2c_driver.c \
../Driver/Src/stm32f303xx_it.c \
../Driver/Src/stm32f303xx_nvic_driver.c \
../Driver/Src/stm32f303xx_rcc_driver.c \
../Driver/Src/stm32f303xx_spi_driver.c \
../Driver/Src/stm32f303xx_tim_driver.c \
../Driver/Src/stm32f303xx_usart_driver.c 

OBJS += \
./Driver/Src/stm32f303xx_can_driver.o \
./Driver/Src/stm32f303xx_dma_driver.o \
./Driver/Src/stm32f303xx_exti_driver.o \
./Driver/Src/stm32f303xx_gpio_driver.o \
./Driver/Src/stm32f303xx_i2c_driver.o \
./Driver/Src/stm32f303xx_it.o \
./Driver/Src/stm32f303xx_nvic_driver.o \
./Driver/Src/stm32f303xx_rcc_driver.o \
./Driver/Src/stm32f303xx_spi_driver.o \
./Driver/Src/stm32f303xx_tim_driver.o \
./Driver/Src/stm32f303xx_usart_driver.o 

C_DEPS += \
./Driver/Src/stm32f303xx_can_driver.d \
./Driver/Src/stm32f303xx_dma_driver.d \
./Driver/Src/stm32f303xx_exti_driver.d \
./Driver/Src/stm32f303xx_gpio_driver.d \
./Driver/Src/stm32f303xx_i2c_driver.d \
./Driver/Src/stm32f303xx_it.d \
./Driver/Src/stm32f303xx_nvic_driver.d \
./Driver/Src/stm32f303xx_rcc_driver.d \
./Driver/Src/stm32f303xx_spi_driver.d \
./Driver/Src/stm32f303xx_tim_driver.d \
./Driver/Src/stm32f303xx_usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/RTT" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Middlewares/SEGGER/SystemView" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/include" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/RTOS_Source/FreeRTOS-Kernel/portable/MemMang" -I../Inc -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Inc" -I"C:/Users/aswin/STM32CubeIDE/workspace_1.19.0/stm32f303xx_driver/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/stm32f303xx_can_driver.cyclo ./Driver/Src/stm32f303xx_can_driver.d ./Driver/Src/stm32f303xx_can_driver.o ./Driver/Src/stm32f303xx_can_driver.su ./Driver/Src/stm32f303xx_dma_driver.cyclo ./Driver/Src/stm32f303xx_dma_driver.d ./Driver/Src/stm32f303xx_dma_driver.o ./Driver/Src/stm32f303xx_dma_driver.su ./Driver/Src/stm32f303xx_exti_driver.cyclo ./Driver/Src/stm32f303xx_exti_driver.d ./Driver/Src/stm32f303xx_exti_driver.o ./Driver/Src/stm32f303xx_exti_driver.su ./Driver/Src/stm32f303xx_gpio_driver.cyclo ./Driver/Src/stm32f303xx_gpio_driver.d ./Driver/Src/stm32f303xx_gpio_driver.o ./Driver/Src/stm32f303xx_gpio_driver.su ./Driver/Src/stm32f303xx_i2c_driver.cyclo ./Driver/Src/stm32f303xx_i2c_driver.d ./Driver/Src/stm32f303xx_i2c_driver.o ./Driver/Src/stm32f303xx_i2c_driver.su ./Driver/Src/stm32f303xx_it.cyclo ./Driver/Src/stm32f303xx_it.d ./Driver/Src/stm32f303xx_it.o ./Driver/Src/stm32f303xx_it.su ./Driver/Src/stm32f303xx_nvic_driver.cyclo ./Driver/Src/stm32f303xx_nvic_driver.d ./Driver/Src/stm32f303xx_nvic_driver.o ./Driver/Src/stm32f303xx_nvic_driver.su ./Driver/Src/stm32f303xx_rcc_driver.cyclo ./Driver/Src/stm32f303xx_rcc_driver.d ./Driver/Src/stm32f303xx_rcc_driver.o ./Driver/Src/stm32f303xx_rcc_driver.su ./Driver/Src/stm32f303xx_spi_driver.cyclo ./Driver/Src/stm32f303xx_spi_driver.d ./Driver/Src/stm32f303xx_spi_driver.o ./Driver/Src/stm32f303xx_spi_driver.su ./Driver/Src/stm32f303xx_tim_driver.cyclo ./Driver/Src/stm32f303xx_tim_driver.d ./Driver/Src/stm32f303xx_tim_driver.o ./Driver/Src/stm32f303xx_tim_driver.su ./Driver/Src/stm32f303xx_usart_driver.cyclo ./Driver/Src/stm32f303xx_usart_driver.d ./Driver/Src/stm32f303xx_usart_driver.o ./Driver/Src/stm32f303xx_usart_driver.su

.PHONY: clean-Driver-2f-Src

