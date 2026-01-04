#include "lis3dsh.h"
#include "spi1.h"

// Registres lis3dsh
#define LIS3DSH_WHO_AM_I   0x0F
#define LIS3DSH_CTRL_REG4  0x20
#define LIS3DSH_CTRL_REG5  0x24
#define LIS3DSH_OUT_X_L    0x28

#define LIS3DSH_CTRL4_ODR   (0x6 << 4) // 100 Hz (ODR3:ODR0 = 0110)
#define LIS3DSH_CTRL4_BDU   (1 << 3) // Block Data Update (output registers not updated until MSB and LSB have been read)
#define LIS3DSH_CTRL4_ZEN   (1 << 2)   
#define LIS3DSH_CTRL4_YEN   (1 << 1)
#define LIS3DSH_CTRL4_XEN   (1 << 0)

#define LIS3DSH_BW_800HZ    (0x0 << 6)  // BW2:BW1 bits 7..6 Anti-aliasing filter 800 Hz
#define LIS3DSH_FS_2G       (0x0 << 3)  // FSCALE2:0 bits 5..3
#define LIS3DSH_ST_DISABLE  (0x0 << 1)  // ST2:ST1 bits 2..1 Self-test disabled
#define LIS3DSH_SIM         (0x0)       // 4-wire interface full-duplex

static void lis3dsh_writereg(uint8_t reg, uint8_t data)
{
    spi1_cs_low();
    spi1_transfer(reg & 0x3F);
    spi1_transfer(data);
    spi1_cs_high();
}

static uint8_t lis3dsh_readreg(uint8_t reg)
{
    uint8_t lVal;

    spi1_cs_low();
    spi1_transfer(0x80 | reg);
    lVal = spi1_transfer(0x00);
    spi1_cs_high();

    return lVal;
}

void lis3dsh_init(void)
{
    uint8_t lId = lis3dsh_readreg(LIS3DSH_WHO_AM_I);
    if (lId != 0x3F)
        return;

uint8_t lCtrl4 =
    LIS3DSH_CTRL4_ODR |  
    LIS3DSH_CTRL4_BDU |                             
    LIS3DSH_CTRL4_ZEN |                             
    LIS3DSH_CTRL4_YEN |                             
    LIS3DSH_CTRL4_XEN;                              

uint8_t lCtrl5 =
    LIS3DSH_BW_800HZ |    
    LIS3DSH_FS_2G |     
    LIS3DSH_ST_DISABLE |
    LIS3DSH_SIM;
    
    lis3dsh_writereg(LIS3DSH_CTRL_REG4, lCtrl4); // 100 Hz, XYZ, BDU
    lis3dsh_writereg(LIS3DSH_CTRL_REG5, lCtrl5); // ±2g
}

void lis3dsh_readxyz(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t lXl, lXh, lYl, lYh, lZl, lZh;

    spi1_cs_low();
    spi1_transfer(0x80 | LIS3DSH_OUT_X_L);

    lXl = spi1_transfer(0x00);
    lXh = spi1_transfer(0x00);
    lYl = spi1_transfer(0x00);
    lYh = spi1_transfer(0x00);
    lZl = spi1_transfer(0x00);
    lZh = spi1_transfer(0x00);

    spi1_cs_high();

    *x = (int16_t)((lXh << 8) | lXl);
    *y = (int16_t)((lYh << 8) | lYl);
    *z = (int16_t)((lZh << 8) | lZl);
}
