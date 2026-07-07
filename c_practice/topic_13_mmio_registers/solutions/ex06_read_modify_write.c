/*
 * ex06_read_modify_write.c - Preserve unrelated bits during update.
 * Key concept: read-modify-write merges only the target bits.
 */
#include <stdint.h>
#include <stdio.h>

#define MASK (0xFUL << 8U)

int main(void)
{
    uint32_t reg = 0xFFFF0000UL;
    reg = (reg & ~MASK) | (0x5UL << 8U);
    printf("reg = 0x%08lX\n", (unsigned long)reg);
    return 0;
}
