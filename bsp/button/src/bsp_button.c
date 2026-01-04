#include "bsp_button.h"
#include "driver_gpio.h"
#include "stm32f4xx.h"

// Carte spécifique : bouton sur PA0
#define BSP_BUTTON_PIN 0
#define BSP_BUTTON_PORT GPIOA

void bsp_button_init(void) {
    // Activer horloge GPIO
     RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configurer PA0 en entrée
    driver_gpio_set_mode(BSP_BUTTON_PORT, BSP_BUTTON_PIN, 0u); // 0 = input
}

BspButtonState bsp_button_getstate(void) {
    // Lire l'état du bouton
    if (driver_gpio_read_pin(BSP_BUTTON_PORT, BSP_BUTTON_PIN) != 0u) {
        return BSP_BUTTON_SET;
    } else {
        return BSP_BUTTON_RESET;
    }
}
