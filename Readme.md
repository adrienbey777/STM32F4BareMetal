<details open>
<summary>Bare-Metal SPI Project – LIS3DSH Accelerometer</summary>

## Overview

This project demonstrates a bare-metal SPI interface with the LIS3DSH accelerometer, developed and debugged using the VS Code environment.
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

## Debugging and flashing

To make development and troubleshooting easier, this project supports real-time debugging using GDB through OpenOCD and the Cortex-Debug extension. This setup provides better insight into sensor values, SPI transactions, and LED behavior, making debugging bare-metal SPI code more reliable and efficient.

![Démo](assets/demo.gif)
</details>

<details >
<summary>Bare-Metal UART Project –  Button Handling</summary>

This part of the project demonstrates bare-metal handling of a user button on the STM32F407 Discovery board, with software debouncing and feedback via LEDs and UART. It has been tested both on hardware and in simulation using Renode, allowing safe and repeatable verification without physical hardware.

## Features

Initialization of the User Button (PA0) as an input.

Polling-based button reading with a software debounce filter to avoid false triggers caused by mechanical bouncing.

Stable button press detection with a counter to validate state changes.

LED feedback: toggles the green LED on each confirmed press.

UART feedback: sends "SET" for a stable press, "RESET" when released, and "BEGIN" at startup.

## Debouncing Logic

The button state is read continuously.

A counter ensures the state is stable for 5 consecutive reads before confirming a change.

Only transitions trigger events, preventing repeated triggers from a single press.

## Testing in Renode

Launch the simulation with the STM32F4BareMetal.resc with renode installed.

Simulate button press and release:

sysbus.gpioPortA.UserButton Press   # simulates pressing PA0
sysbus.gpioPortA.UserButton Release # simulates releasing PA0

</details>
