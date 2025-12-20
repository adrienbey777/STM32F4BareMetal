#include <stdint.h>
#include "main_spi.h"
#include "main_uart.h"
#include "led.h"

#define USE_MAIN 2

int main(void)
{
    led_init();
    // préprocesseur C, exécuté avant la compilation, selon la macro définie, un seul bloc est compilé
#if USE_MAIN == 1
    main_spi();
#elif USE_MAIN == 2
    main_uart();
#else
#error "USE_MAIN must be 1 or 2"
#endif

    while (1)
        ; /* sécurité */
}
