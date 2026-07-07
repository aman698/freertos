/*
 * ex03_precedence.c — Operator precedence without vs with parentheses
 * Key concept: bitwise AND binds tighter than comparison in some mixes — use ().
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t reg = 0x00000050UL; /* bits 4 and 6 set */

    /* Wrong mental model: reg & 0x10 == 0x10  parsed as reg & (0x10 == 0x10) */
    uint32_t wrong = reg & 0x10 == 0x10;

    /* Correct: (reg & 0x10) == 0x10 */
    uint32_t right = (reg & 0x10) == 0x10;

    printf("reg = 0x%08lX\n", (unsigned long)reg);
    printf("Without parens (reg & 0x10 == 0x10): %lu\n", (unsigned long)wrong);
    printf("With parens    ((reg & 0x10) == 0x10): %lu\n", (unsigned long)right);

    /* Arithmetic: 2 + 3 * 4 vs (2 + 3) * 4 */
    printf("2 + 3 * 4 = %d\n", 2 + 3 * 4);
    printf("(2 + 3) * 4 = %d\n", (2 + 3) * 4);

    return 0;
}
