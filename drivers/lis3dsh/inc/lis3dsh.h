#ifndef LIS3DSH_H
#define LIS3DSH_H

#include <stdint.h>  

void lis3dsh_init(void);

void lis3dsh_readxyz(int16_t *x, int16_t *y, int16_t *z);

#endif /* LIS3DSH_H */
