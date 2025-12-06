STM32F4_BareMetal/
├── cmsis-device-f4/      # cloné depuis GitHub
│   ├── Include/
│   └── Source/
├── src/
│   ├── main.c
│   └── startup.c
│   └── syscalls.c
├── drivers/
│   └── UART/
│       ├── uart.c
│       └── uart.h
├── linker/
│   └── stm32f4.ld
├── Makefile
└── run.resc
make 

& "C:\Program Files\Renode\bin\Renode.exe" "C:\Users\adrie\Project_Github\STM32F4\STM32F4_BareMetal\STM32F4BareMetal.resc"BareMetal>