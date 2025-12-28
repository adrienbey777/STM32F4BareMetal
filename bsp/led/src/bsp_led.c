#include "stm32f4xx.h"
#include "bsp_led.h"


static const uint8_t bsp_led_pin[] =
{
    12, // BSP_LED_GREEN
    13, // BSP_LED_ORANGE
    14, // BSP_LED_RED
    15  // BSP_LED_BLUE
};

static void bsp_led_gpio_enable_clock(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}

static void bsp_led_init_pins (void)
{
    for (int i = 0; i < 4; i++)
    {
        GPIOD->MODER &= ~(3U << (bsp_led_pin[i] * 2));
        GPIOD->MODER |=  (1U << (bsp_led_pin[i] * 2));
    }
}

void bsp_led_init(void)
{
    bsp_led_gpio_enable_clock();
    bsp_led_init_pins();
}

void bsp_led_on(uint8_t led)
{
    GPIOD->ODR |= (1U << bsp_led_pin[led]);
}

void bsp_led_off(uint8_t led)
{
    GPIOD->ODR &= ~(1U << bsp_led_pin[led]);
}

void bsp_led_toggle(uint8_t led)
{
    GPIOD->ODR ^= (1U << bsp_led_pin[led]);
}
