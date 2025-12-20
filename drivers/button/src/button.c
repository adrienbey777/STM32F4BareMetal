#include "button.h"
#include "stm32f4xx.h"  

void button_init(void)
{
    // Activer l’horloge GPIOA
    RCC->AHB1ENR |= (1 << BUTTON_RCC);

    // Configurer PA0 comme entrée
    BUTTON_PORT->MODER &= ~(0x3 << (BUTTON_PIN * 2));  // 00 = input
    BUTTON_PORT->PUPDR &= ~(0x3 << (BUTTON_PIN * 2));  // pas de pull-up/pull-down
}

ButtonState button_read(void)
{
    if (BUTTON_PORT->IDR & (1 << BUTTON_PIN))
        return BUTTON_SET;
    else
        return BUTTON_RESET;
}
