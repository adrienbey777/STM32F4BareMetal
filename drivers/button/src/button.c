#include "button.h"
#include "bsp_button.h"

#define DEBOUNCE_CNT_MAX 5

static BspButtonState last_raw;
static BspButtonState stable;
static uint8_t     cnt;

void button_init(void)
{
    /* Initialisation hardware via BSP */
    bsp_button_init();

    last_raw = BSP_BUTTON_RESET;
    stable   = BSP_BUTTON_RESET;
    cnt      = 0;
}

ButtonEvent button_update(void)
{
    BspButtonState raw = bsp_button_getstate();

    if (raw == last_raw)
    {
        if (cnt < DEBOUNCE_CNT_MAX)
        {
            cnt++;
        }
    }
    else
    {
        cnt = 0;
    }

    /* Mémorisation de l'état brut pour la prochaine itération */

    last_raw = raw;

    /*  Si l'état brut est resté identique DEBOUNCE_CNT_MAX */

    if (cnt >= DEBOUNCE_CNT_MAX)
    {
        if ((raw == BSP_BUTTON_SET) && (stable == BSP_BUTTON_RESET))
        {
            stable = BSP_BUTTON_SET;
            return BUTTON_EVENT_SET;
        }
        else if ((raw == BSP_BUTTON_RESET) && (stable == BSP_BUTTON_SET))
        {
            stable = BSP_BUTTON_RESET;
            return BUTTON_EVENT_RESET;
        }
    }

    return BUTTON_EVENT_NONE;
}
