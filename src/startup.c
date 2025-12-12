#include <stdint.h>


// Déclarations des handlers

void Reset_Handler(void);
void NMI_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)       __attribute__((weak, alias("Default_Handler")));


// Pile initiale (Stack Pointer)

extern uint32_t _estack; 


// Table des vecteurs

__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))(&_estack),  
    Reset_Handler,               
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,0,0,0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler
};


// Reset_Handler

extern int main(void);
extern void SystemInit(void);  // si CMSIS utilisé

void Reset_Handler(void)
{
    SystemInit();  // initialise l’horloge, si CMSIS
    main();        // appel de main
    while(1);      // sécurité si main retourne
}

// Default Handler

void Default_Handler(void)
{
    while(1);
}
