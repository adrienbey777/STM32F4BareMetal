#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include <stdint.h>

/* Événements générés par le bouton :
 *         - BUTTON_EVENT_NONE  : aucun changement
 *         - BUTTON_EVENT_SET   : appui détecté
 *         - BUTTON_EVENT_RESET : relâchement détecté
 */
typedef enum
{
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_SET,
    BUTTON_EVENT_RESET
} ButtonEvent;


void button_init(void);

ButtonEvent button_update(void);

#endif /* BUTTON_DRIVER_H */
