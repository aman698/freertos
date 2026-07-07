/*
 * ex10_feature_flags.c — Compile-time feature toggles
 * Key concept: USE_* macros enable/disable driver modules at build time.
 */
#include <stdint.h>
#include <stdio.h>

#define USE_UART 1
#define USE_SPI  1
#define USE_I2C  0

int main(void)
{
    printf("Enabled drivers:\n");
#if USE_UART
    printf("  - UART\n");
#endif
#if USE_SPI
    printf("  - SPI\n");
#endif
#if USE_I2C
    printf("  - I2C\n");
#endif
    return 0;
}
