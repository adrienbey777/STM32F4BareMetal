# Toolchain

CC = arm-none-eabi-gcc

CPUFLAGS = -mcpu=cortex-m4 -mthumb

CFLAGS = $(CPUFLAGS) -O0 -g -ffreestanding -nostartfiles \
         -Icmsis-device-f4/Include \
         -Icmsis-device-f4/core/Include \
         -Idrivers/uart/inc \
         -Idrivers/gpio/inc \
         -Idrivers/spi/inc \
         -Ibsp/spi/inc \
         -Ibsp/uart/inc \
         -Ibsp/button/inc \
         -Ibsp/led/inc \
         -Iiopl/uart/inc \
         -Iiopl/led/inc \
         -Iiopl/spi1/inc \
         -Iiopl/button/inc \
         -Idevices/lis3dsh/inc \
         -Iinc \
         -DSTM32F407xx

LDFLAGS = $(CPUFLAGS) -T linker/stm32f4.ld


# Sources 
SRC = \
drivers/spi/src/driver_spi.c \
drivers/uart/src/driver_uart.c \
drivers/gpio/src/driver_gpio.c \
bsp/spi/src/bsp_spi1.c \
bsp/uart/src/bsp_uart.c \
bsp/button/src/bsp_button.c \
bsp/led/src/bsp_led.c \
iopl/uart/src/uart.c \
iopl/led/src/led.c \
iopl/spi1/src/spi1.c \
iopl/button/src/button.c \
devices/lis3dsh/src/lis3dsh.c \
src/startup.c \
src/main.c \
src/main_spi.c \
src/main_uart.c \
src/syscalls.c \
src/delay.c \
cmsis-device-f4/Source/Templates/system_stm32f4xx.c


# Build

BUILD_DIR = build
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

ELF = $(BUILD_DIR)/firmware.elf

# Rules

all: $(ELF)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(BUILD_DIR)
