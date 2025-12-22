#include "lis3dsh.h"
#include "spi1.h"
#include "bsp_spi1.h"

// Registres lis3dsh
#define LIS3DSH_WHO_AM_I   0x0F
#define LIS3DSH_CTRL_REG4  0x20
#define LIS3DSH_CTRL_REG5  0x24
#define LIS3DSH_OUT_X_L    0x28

static void lis3dsh_writereg(uint8_t reg, uint8_t data)
{
    bsp_spi1_lis3dsh_cs_low();
    spi1_transfer(reg & 0x3F);
    spi1_transfer(data);
    bsp_spi1_lis3dsh_cs_high();
}

static uint8_t lis3dsh_readreg(uint8_t reg)
{
    uint8_t lVal;

    bsp_spi1_lis3dsh_cs_low();
    spi1_transfer(0x80 | reg);
    lVal = spi1_transfer(0x00);
    bsp_spi1_lis3dsh_cs_high();

    return lVal;
}

void lis3dsh_init(void)
{
    uint8_t lId = lis3dsh_readreg(LIS3DSH_WHO_AM_I);
    if (lId != 0x3F)
        return;

    lis3dsh_writereg(LIS3DSH_CTRL_REG4, 0xE7); // 100 Hz, XYZ, BDU
    lis3dsh_writereg(LIS3DSH_CTRL_REG5, 0x00); // ±2g
}

void lis3dsh_readxyz(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t lXl, lXh, lYl, lYh, lZl, lZh;

    bsp_spi1_lis3dsh_cs_low();
    spi1_transfer(0x80 | LIS3DSH_OUT_X_L);

    lXl = spi1_transfer(0x00);
    lXh = spi1_transfer(0x00);
    lYl = spi1_transfer(0x00);
    lYh = spi1_transfer(0x00);
    lZl = spi1_transfer(0x00);
    lZh = spi1_transfer(0x00);

    bsp_spi1_lis3dsh_cs_high();

    *x = (int16_t)((lXh << 8) | lXl);
    *y = (int16_t)((lYh << 8) | lYl);
    *z = (int16_t)((lZh << 8) | lZl);
}
