/*
 * ex01_stdint_sizes.c — Print sizeof for fixed-width types
 * Key concept: sizeof returns bytes; embedded code uses explicit widths.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    printf("=== Fixed-width type sizes (bytes) ===\n");
    printf("sizeof(uint8_t)  = %zu\n", sizeof(uint8_t));
    printf("sizeof(uint16_t) = %zu\n", sizeof(uint16_t));
    printf("sizeof(uint32_t) = %zu\n", sizeof(uint32_t));
    printf("sizeof(int8_t)   = %zu\n", sizeof(int8_t));
    printf("sizeof(int16_t)  = %zu\n", sizeof(int16_t));
    printf("sizeof(int32_t)  = %zu\n", sizeof(int32_t));

    /* Embedded rule: match register width — STM32 GPIO ODR is 16-bit */
    printf("\nTip: use uint16_t for 16-bit hardware registers.\n");
    return 0;
}
