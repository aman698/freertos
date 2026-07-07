/*
 * ex04_field_write.c - Write a multi-bit register field.
 * Key concept: clear field mask before inserting a new value.
 */
#include <stdint.h>
#include <stdio.h>

#define FIELD_POS  4U
#define FIELD_MASK (3UL << FIELD_POS)

static uint32_t write_field(uint32_t reg, uint32_t value)
{
    reg &= ~FIELD_MASK;
    reg |= ((value & 3UL) << FIELD_POS);
    return reg;
}

int main(void)
{
    uint32_t moder = write_field(0U, 2U);
    printf("MODER = 0x%08lX\n", (unsigned long)moder);
    return 0;
}
