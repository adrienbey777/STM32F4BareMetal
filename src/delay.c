#include <stdint.h>
#include "delay.h"

// on force le comillateur à ne pas optimiser cette boucle
void delay(volatile uint32_t loops)
{
    volatile uint32_t i;
    for (i = 0; i < loops; ++i) {
        __asm__("nop"); //__asm__ instruction assembleur dans du C, "nop" no operation, 1 cycle CPU
    }
}

