# Bare-Metal SPI Project – LIS3DSH Accelerometer
## Overview

This project demonstrates a bare-metal SPI interface with the LIS3DSH accelerometer.
The accelerometer data is read directly from the sensor registers, and LEDs are controlled based on the X and Y axis orientation of the board.

The goal of this project is to gain hands-on experience with:

- Low-level SPI communication

- Bare-metal embedded programming

- MEMS sensor configuration and data acquisition

- GPIO control based on sensor inputs

## Hardware

STM32F407 Discovery

LIS3DSH accelerometer

On-board LEDs (Red, Green, Blue, Orange)

## Technologies

C

Bare-metal programming

SPI communication

GPIO

ARM GCC toolchain

## Project Functionality

SPI peripheral initialization

LIS3DSH configuration (normal mode, X/Y axes enabled)

Periodic reading of raw acceleration values

LED control based on board orientation

Threshold-based logic with hysteresis to ensure stable behavior

LED Control Logic
Y Axis

Positive Y acceleration → Orange LED ON

Negative Y acceleration → Blue LED ON

X Axis

Positive X acceleration → Red LED ON

Negative X acceleration → Green LED ON

## Debugging

To make development and troubleshooting easier, this project supports real-time debugging using OpenOCD together with VS Code and the Cortex-Debug extension.
This addition provides better insight into sensor values, SPI transactions, and LED behavior, making debugging bare-metal SPI code more reliable and efficient. 

![Démo](assets/demo.gif)
