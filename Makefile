# Toolchain

CC = arm-none-eabi-gcc

CPUFLAGS = -mcpu=cortex-m4 -mthumb

CFLAGS = $(CPUFLAGS) -O0 -g -ffreestanding -nostartfiles \
         -Icmsis-device-f4/Include \
         -Icmsis-device-f4/core/Include \
         -Ibsp/spi/inc \
         -Idrivers/uart/inc \
         -Idrivers/led/inc \
         -Idrivers/spi1/inc \
         -Idrivers/lis3dsh/inc \
         -Idrivers/button/inc \
         -Iinc \
         -DSTM32F407xx

LDFLAGS = $(CPUFLAGS) -T linker/stm32f4.ld


# Sources 
SRC = \
bsp/spi/src/bsp_spi1.c \
drivers/uart/src/uart.c \
drivers/led/src/led.c \
drivers/spi1/src/spi1.c \
drivers/button/src/button.c \
drivers/lis3dsh/src/lis3dsh.c \
src/startup.c \
src/main.c \
src/main_spi.c \
src/main_uart.c \
src/syscalls.c \
src/delay.c \
src/system_spi.c \
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
