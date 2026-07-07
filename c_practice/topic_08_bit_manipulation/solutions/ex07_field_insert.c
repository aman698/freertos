/*
 * ex07_field_insert.c — Insert value into bit field
 * Key concept: clear field mask then OR new value shifted to position.
 */
#include <stdint.h>
#include <stdio.h>

#define FIELD_MASK(pos, width) \
    (((1UL << (width)) - 1UL) << (pos))

#define FIELD_SET(reg, pos, width, val) \
    do { \
        (reg) = ((reg) & ~FIELD_MASK(pos, width)) | \
                (((val) & ((1UL << (width)) - 1UL)) << (pos)); \
    } while (0)

int main(void)
{
    uint32_t moder = 0x00000000UL;

    FIELD_SET(moder, 10U, 2U, 1U);  /* PA5 MODER = 01 (output) */
    printf("MODER after set PA5 to output: 0x%08lX\n", (unsigned long)moder);
    return 0;
}
