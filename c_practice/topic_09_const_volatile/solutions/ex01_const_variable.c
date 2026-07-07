/*
 * ex01_const_variable.c — const variables cannot be assigned after init
 * Key concept: const data may live in flash on embedded targets.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint32_t sysclk_hz = 84000000UL;
    const uint8_t led_pin = 5U;

    printf("SYSCLK = %lu Hz, LED pin = PA%u\n",
           (unsigned long)sysclk_hz, led_pin);
    return 0;
}
