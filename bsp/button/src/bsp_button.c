#include "bsp_button.h"
#include "driver_button.h"
#include "stm32f4xx.h"

// Carte spécifique : bouton sur PA0
#define BSP_BUTTON_PIN 0
#define BSP_BUTTON_PORT GPIOA
#define BSP_BUTTON_CLK  RCC_AHB1ENR_GPIOAEN

void bsp_button_init(void) {
    // Activer horloge GPIO
    driver_button_enable_clock(BSP_BUTTON_PORT, BSP_BUTTON_CLK);

    // Configurer PA0 en entrée
    driver_button_set_mode(BSP_BUTTON_PORT, BSP_BUTTON_PIN, 0); // 0 = input
}

BspButtonState bsp_button_getstate(void) {
    if (driver_button_read_pin(BSP_BUTTON_PORT, BSP_BUTTON_PIN) != 0) {
        return BSP_BUTTON_SET;
    } else {
        return BSP_BUTTON_RESET;
    }
}
