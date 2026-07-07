/*
 * ex09_reserved_bits.c - Do not modify reserved register bits.
 * Key concept: mask writes to documented bits only.
 */
#include <stdint.h>
#include <stdio.h>

#define ENABLE_BIT      (1UL << 0U)
#define DOCUMENTED_MASK (1UL << 0U)

int main(void)
{
    uint32_t reg = 0xFFFF0000UL; /* Upper bits represent reserved state. */
    reg = (reg & ~DOCUMENTED_MASK) | ENABLE_BIT;
    printf("reserved preserved reg=0x%08lX\n", (unsigned long)reg);
    return 0;
}
