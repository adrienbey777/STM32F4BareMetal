#include "stm32f4xx.h"
#include "bsp_system_clock.h"

void bsp_system_clock_init(void)
{
    
    // Activer le cristal externe HSE (8 MHz)
    
    RCC->CR |= RCC_CR_HSEON; // Mettre le bit HSEON à 1 pour activer le HSE
    while (!(RCC->CR & RCC_CR_HSERDY))
        ; // Attendre que le HSE soit stable (HSERDY = 1)

    
    // Configurer le Flash pour haute fréquence
    
    FLASH->ACR = FLASH_ACR_LATENCY_5WS; // 5 wait states pour SYSCLK = 168 MHz
                                        // Important : sinon le CPU risque de lire trop vite la Flash

    
    // Configurer la PLL pour monter à 168 MHz
    
    // PLL source = HSE (8 MHz)
    // PLLM = 8  -> divise HSE : 8 MHz / 8 = 1 MHz
    // PLLN = 336 -> multiplie : 1 MHz * 336 = 336 MHz
    // PLLP = 2  -> divise PLL clock : 336 MHz / 2 = 168 MHz SYSCLK
    RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos) |   // PLLM
                   (336 << RCC_PLLCFGR_PLLN_Pos) | // PLLN
                   (0 << RCC_PLLCFGR_PLLP_Pos) |   // PLLP = 2
                   RCC_PLLCFGR_PLLSRC_HSE;         // PLL source HSE

    RCC->CR |= RCC_CR_PLLON; // Activer la PLL
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ; // Attendre que la PLL soit stable

    
    // Configurer les prescalers
    
    // APB1 = 42 MHz pour UART2 (max 42 MHz sur APB1)
    // AHB = SYSCLK / 1 = 168 MHz
    RCC->CFGR = RCC_CFGR_HPRE_DIV1 | // AHB prescaler = 1 → HCLK = 168 MHz
                RCC_CFGR_PPRE1_DIV4; // APB1 prescaler = 4 → PCLK1 = 42 MHz

    
    // Basculer le SYSCLK sur la PLL
    
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Sélectionner la PLL comme source du SYSCLK
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ; // Attendre que le switch soit effectif
}