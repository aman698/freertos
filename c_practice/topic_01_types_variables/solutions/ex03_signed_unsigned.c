/*
 * ex03_signed_unsigned.c — Comparison trap with mixed signed/unsigned
 * Key concept: -1 converted to unsigned becomes a large positive value.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    int8_t  signed_err   = -1;   /* e.g. sensor error code */
    uint8_t raw_byte     = 255;  /* e.g. 0xFF on the wire */
    int     loop_index   = -1;

    printf("signed_err = %d, raw_byte = %u\n", signed_err, raw_byte);

    /* Same bit pattern in 8 bits, but different types */
    if ((uint8_t)signed_err == raw_byte) {
        printf("Bit patterns match: (uint8_t)(-1) == 255\n");
    }

    /* Classic bug: comparing signed negative to unsigned */
    if (loop_index < (uint32_t)10) {
        printf("loop_index < 10u is TRUE (because -1 becomes huge unsigned)\n");
    }

    /* Fix: cast both sides consistently or use signed type */
    if (loop_index < 10) {
        printf("Correct compare with int: loop_index < 10 is TRUE\n");
    }

    return 0;
}
