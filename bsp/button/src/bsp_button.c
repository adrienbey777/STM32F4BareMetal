#include "stm32f4xx.h" 
#include "bsp_button.h"

void bsp_button_init(void)
{
    // Activer l'horloge GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA0 en entrée
    GPIOA->MODER &= ~(0x3 << (0 * 2));
    GPIOA->PUPDR &= ~(0x3 << (0 * 2));
}

BspButtonState bsp_button_getstate(void)
{
    if (GPIOA->IDR & (1 << 0))
        return BSP_BUTTON_SET;
    else
        return BSP_BUTTON_RESET;
}
