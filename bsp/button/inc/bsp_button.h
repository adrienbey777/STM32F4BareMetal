#ifndef BUTTON_BSP_H
#define BUTTON_BSP_H

typedef enum
{
    BSP_BUTTON_RESET,
    BSP_BUTTON_SET
} BspButtonState;

void bsp_button_init(void);
BspButtonState bsp_button_getstate(void);

#endif
