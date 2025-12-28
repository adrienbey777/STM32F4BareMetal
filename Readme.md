<details open>
# STM32F4 Bare-Metal

---

## Table of Contents
1. [Overview](#overview)
2. [Hardware](#hardware)
3. [Technologies](#technologies)
4. [Debugging and flashing](#Debugging-and-flashing)
5. [Project Examples](#project-examples)

---

## Overview
This repository contains bare-metal projects for the **STM32F407 Discovery board**.  
It demonstrates low-level peripheral programming (SPI, UART, GPIO) without an RTOS, providing a foundation to learn embedded systems development.

The projects are divided into independent examples, each with its own `main` file:
- `main_spi.c` → SPI project (LIS3DSH accelerometer + LED control)
- `main_uart.c` → UART project (User button + LED feedback)

Common drivers for GPIO, SPI, and UART are shared across all projects

## Debugging and flashing

To make development and troubleshooting easier, this project supports real-time debugging using GDB through OpenOCD and the Cortex-Debug extension. This setup provides better insight into sensor values, SPI transactions, and LED behavior, making debugging bare-metal SPI code more reliable and efficient.

## Project Examples

### 1. SPI – LIS3DSH Accelerometer (`main_spi.c`)
This example demonstrates how to use the SPI bus to communicate with the LIS3DSH accelerometer and control the LEDs on the STM32F4 board based on the sensor's orientation.
In main.c, you have to set #define USE_MAIN: 1 for the SPI project, 2 for the UART project
**How it works:**
- The SPI peripheral is initialized to communicate with the LIS3DSH.
- The accelerometer is configured in normal mode with X and Y axes enabled.
- The board periodically reads raw acceleration values from the sensor.
- LEDs are turned on according to the measured orientation:
  - Y axis: positive → Orange LED, negative → Blue LED
  - X axis: positive → Red LED, negative → Green LED
- A hysteresis logic is applied to prevent rapid LED blinking.

---
![Démo](assets/demo.gif)



### 2. UART – User Button (`main_uart.c`)
This example demonstrates how to handle the user button input and send feedback via UART while providing visual feedback using the LEDs.

**How it works:**
- The user button is configured as an input and managed with software debounce to avoid false triggers.
- The UART is initialized to allow sending messages when the button is pressed.
- Reading the button state triggers the  Green LED to provide immediate visual feedback.
- The program runs in an infinite loop to continuously monitor the button and update the LED in real time.

On renode :
Launch the simulation with the STM32F4BareMetal.resc with renode installed.
Simulate button press and release:
sysbus.gpioPortA.UserButton Press   # simulates pressing PA0
sysbus.gpioPortA.UserButton Release # simulates releasing PA0

---

Both projects share the same **low-level drivers** for GPIO, SPI, and UART, making the code reusable and maintaining a clear project structure.

