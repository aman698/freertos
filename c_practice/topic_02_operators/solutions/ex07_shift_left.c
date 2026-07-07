/*
 * ex07_shift_left.c — Create pin mask with left shift
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const unsigned pin = 5U;
    uint32_t mask = (1U << pin);

    printf("Mask for bit %u: 0x%04lX\n", pin, (unsigned long)mask);
    return 0;
}
