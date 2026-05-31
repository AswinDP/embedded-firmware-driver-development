# Embedded Firmware Driver Development

This repository documents my journey of learning and developing embedded firmware from the ground up.

The focus of this repository is understanding how embedded software is built beneath vendor SDKs and middleware by implementing peripherals, drivers, and firmware components at the register level. Along the way, the project also explores firmware architecture, API design, RTOS concepts, bootloaders, and platform-specific development.

## Platforms

### STM32

The STM32 section contains register-level peripheral drivers and example applications developed to understand microcontroller internals and embedded software design.

Implemented and ongoing work includes:

* GPIO
* RCC
* NVIC
* EXTI
* USART
* SPI
* I2C
* CAN
* DMA
* Timers
* FreeRTOS integration

Planned additions:

* ADC
* Watchdog Timers
* Bootloader Development
* Advanced Timer Features
* Power Management

### nRF52

The nRF52 section focuses on understanding Nordic Semiconductor devices through register-level peripheral development and SDK-style API design.

Planned areas of exploration include:

* GPIO
* CLOCK
* POWER
* GPIOTE
* TIMER
* RTC
* PPI
* UARTE
* SPIM
* TWIM
* SAADC
* PWM
* Watchdog
* Flash Memory Controller

The goal is not only to develop drivers but also to understand how Nordic SDKs and modern embedded frameworks are structured internally.

## Repository Goals

* Develop peripheral drivers from reference manuals and datasheets.
* Learn embedded firmware architecture beyond application-level programming.
* Design clean and reusable driver APIs.
* Understand how vendor SDKs are implemented internally.
* Explore bootloaders, RTOS integration, middleware, and firmware frameworks.
* Build a strong foundation in embedded systems engineering through hands-on development.

This repository is expected to evolve continuously as new peripherals, firmware components, and embedded software concepts are explored.
