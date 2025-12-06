# Toolchain
CC = arm-none-eabi-gcc

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -O2 -nostartfiles -ffreestanding \
         -Icmsis-device-f4/Include \
         -Icmsis-device-f4/core/Include \
         -IDrivers \
         -DSTM32F407xx

LDFLAGS = -T linker/stm32f4.ld

# Sources
SRC = Src/startup.c \
      Src/main.c \
      Src/syscalls.c \
      drivers/uart/src/uart.c \
      cmsis-device-f4/Source/Templates/system_stm32f4xx.c

# Build directory
BUILD_DIR = build

# Objects (aplatis : tous dans build/)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC)))

# ELF
ELF = $(BUILD_DIR)/firmware.elf

# Créer le dossier build si nécessaire
$(shell mkdir -p $(BUILD_DIR))

# Targets
all: $(ELF)

# Compile .c -> .o
$(BUILD_DIR)/%.o:
	$(CC) $(CFLAGS) -c $(firstword $(filter %$*.c,$(SRC))) -o $@

# Link .o -> .elf
$(ELF): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)/*
