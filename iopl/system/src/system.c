#include "system.h"
#include "bsp_system_clock.h"
void system_init(void)
{
    bsp_system_clock_init();   // initialise le SYSCLK / bus
}

