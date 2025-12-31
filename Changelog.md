# Changelog

All notable changes to this STM32F4 bare-metal project are documented here.  

## [v0.0] - 2024-12-30
### Added
- Initial functional bare-metal STM32F4 project
- Two separate main files: main_spi.c and main_uart.c. Select one using USE_MAIN in main.c.  
- Basic folder structure for BSP modules (`bsp/led`, `bsp/button`, `bsp/uart`, `bsp/spi`)
- Basic drivers for LEDs, buttons, UART, and SPI
- Startup file and linker script for STM32F407