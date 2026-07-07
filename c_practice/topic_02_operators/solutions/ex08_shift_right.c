/*
 * ex08_shift_right.c — Extract nibbles with shift and AND
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t byte = 0xA5U;
    uint8_t upper = (byte >> 4) & 0x0FU;
    uint8_t lower = byte & 0x0FU;

    printf("byte=0x%02X upper=0x%X lower=0x%X\n", byte, upper, lower);
    return 0;
}
