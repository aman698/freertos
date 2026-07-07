/*
 * ex01_register_variable.c - Simulate a memory-mapped register.
 * Key concept: volatile prevents register accesses from being optimized away.
 */
#include <stdint.h>
#include <stdio.h>

static volatile uint32_t SIM_REG;

int main(void)
{
    SIM_REG = 0x12345678UL;
    printf("SIM_REG = 0x%08lX\n", (unsigned long)SIM_REG);
    return 0;
}
