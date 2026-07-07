/*
 * ex02_uint8_max.c — UINT8_MAX and unsigned wrap
 * Key concept: uint8_t overflow wraps modulo 256 (defined behavior).
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t pwm_duty = UINT8_MAX; /* 255 = 100% in 8-bit PWM table */

    printf("PWM duty (max): %u\n", pwm_duty);
    printf("UINT8_MAX = %u\n", UINT8_MAX);

    pwm_duty++; /* 255 + 1 wraps to 0 */
    printf("After increment: %u (wrapped to 0)\n", pwm_duty);

    pwm_duty = 250;
    pwm_duty += 10; /* 260 mod 256 = 4 */
    printf("250 + 10 as uint8_t = %u\n", pwm_duty);

    return 0;
}
