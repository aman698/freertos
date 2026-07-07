/*
 * ex06_token_paste.c — ## concatenates tokens into one identifier
 * Key concept: GPIOA_ODR from GPIO + A + _ODR via token pasting.
 */
#include <stdint.h>
#include <stdio.h>

#define MAKE_REG(periph, name) periph##_##name
#define GPIOA_ODR 0x40020014UL

int main(void)
{
    uint32_t addr = MAKE_REG(GPIOA, ODR);
    printf("GPIOA ODR address = 0x%08lX\n", (unsigned long)addr);
    return 0;
}
