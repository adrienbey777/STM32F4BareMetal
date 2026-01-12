<details open>
<summary>STM32F4 Bare-Metal</summary>
  
## Table of Contents
1. [Overview](#overview)
2. [Hardware](#hardware)
3. [Tools and Environment](#Tools-and-Environment)
4. [Debugging and flashing](#Debugging-and-flashing)
5. [Project Examples](#project-examples)

---

## Overview
This repository contains bare-metal projects for the **STM32F407 Discovery board**.  
It demonstrates low-level peripheral programming (SPI, UART, GPIO) without an RTOS, providing a foundation to learn embedded systems development.

The projects are divided into independent examples, each with its own `main` file:
- `main_spi.c` → SPI project (LIS3DSH accelerometer + LED control)
- `main_uart.c` → UART project (User button + LED feedback)  
In main.c, you have to set #define USE_MAIN: 1 for the SPI project, 2 for the UART project.

Common drivers for GPIO, SPI, and UART are shared across all projects

## Hardware

**Main components:**
- **STM32F407** microcontroller (ARM Cortex-M4)
- **LIS3DSH accelerometer** (connected via SPI, used in the SPI example)
- **On-board LEDs**:
  - Green (PD12)
  - Orange (PD13)
  - Red (PD14)
  - Blue (PD15)
- **User button** (PA0, used in the UART example)

**Toolchain and tools:**
- **ARM GNU Toolchain** for compiling and linking the firmware
- **Make** for build automation
- **OpenOCD** for flashing and on-target debugging
- **GDB** for source-level debugging
- **Cortex-Debug (VS Code extension)** for an integrated debugging experience
- **Renode** for hardware simulation and testing without a physical board

**Software environment:**
- Bare-metal C programming (no RTOS, no HAL)
- CMSIS device headers for register definitions
- Custom low-level drivers for GPIO, SPI, and UART


## Debugging and Flashing

To make development and troubleshooting easier, this project supports real-time debugging using **GDB** through **OpenOCD** and the **Cortex-Debug** extension. This setup provides better insight into sensor values, SPI transactions, and LED behavior, making debugging bare-metal code more reliable and efficient.

Build the project:  
make MAIN=main_spi or MAIN=main_uart.
This will generate a firmware.elf file if the build succeeds.

Clean build artifacts:  
make clean

Debugging and flashing using launch.json:  
The launch.json configuration (for VSCode) is preconfigured to work with OpenOCD and the STM32F407 Discovery board.

## Project Examples
<details>
<summary>1. SPI – LIS3DSH Accelerometer (`main_spi.c`)</summary>
<p></p>  
This example demonstrates how to use the SPI bus to communicate with the LIS3DSH accelerometer and control the LEDs on the STM32F4 board based on the sensor's orientation.
  
**How it works:**  
- The SPI peripheral is initialized to communicate with the LIS3DSH.    
- The accelerometer is configured in normal mode with X and Y axes enabled.  
- The board periodically reads raw acceleration values from the sensor.   
- LEDs are turned on according to the measured orientation:  
  - Y axis: positive → Orange LED, negative → Blue LED    
  - X axis: positive → Red LED, negative → Green LED   
- A hysteresis logic is applied to prevent rapid LED blinking.   

![Démo](assets/demo.gif)

</details>

<details>
<summary>2. UART – User Button (`main_uart.c`)</summary>  
<p></p>  
This example demonstrates how to handle the user button input and send feedback via UART while providing visual feedback using the LEDs.

**How it works:**
- The user button is configured as an input and managed with software debounce to avoid false triggers.
- The UART is initialized to allow sending messages when the button is pressed and released.
- Reading the button state triggers the  Green LED to provide immediate visual feedback.
- The program runs in an infinite loop to continuously monitor the button and update the LED in real time.

On renode :
Launch the simulation with the STM32F4BareMetal.resc with renode installed. 
Simulate button press and release: 
sysbus.gpioPortA.UserButton Press   # simulates pressing PA0 
sysbus.gpioPortA.UserButton Release # simulates releasing PA0 

Update (12/01/2026) : 
I connected the PA2 (TX) pin of the microcontroller to the RX pin of the CP2102 (and GND with GND) in order to verify proper UART communication. 
The tests were carried out using Tera Term, configured with a 115200 baud rate, 8 data bits, no parity, 1 stop bit (8N1), and no flow control. 
The corresponding serial port was selected, and messages were transmitted to validate data transmission. 
<img width="483" height="162" alt="tera_main_uart" src="https://github.com/user-attachments/assets/f599e93c-dc72-4742-b37e-ae792b2a17f1" />
![STM32 with CP2102](https://github.com/user-attachments/assets/5faaac51-8cf3-4e97-8de7-0121a3f80bb4)

</details>
