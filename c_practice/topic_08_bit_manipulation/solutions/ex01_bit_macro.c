/*
 * ex01_bit_macro.c — BIT(n) macro for readable pin masks
 * Key concept: BIT(n) expands to (1UL << n) for 32-bit register work.
 */
#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1UL << (n))

int main(void)
{
    printf("BIT(0)  = 0x%08lX\n", (unsigned long)BIT(0));
    printf("BIT(5)  = 0x%08lX  (PA5 / LD2 on NUCLEO)\n", (unsigned long)BIT(5));
    printf("BIT(13) = 0x%08lX  (PC13 user button)\n", (unsigned long)BIT(13));
    return 0;
}
