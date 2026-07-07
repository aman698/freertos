/*
 * ex04_pointer_arithmetic.c — Walk buffer with pointer increment
 * Key concept: ptr++ advances by sizeof(pointed-to type) bytes.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint8_t frame[] = { 0xAA, 0x55, 0x01, 0x10, 0xFF };
    const uint8_t *p = frame;
    const uint8_t *end = frame + sizeof(frame);

    printf("Frame bytes via pointer walk:\n");
    while (p < end) {
        printf("  addr=%p  byte=0x%02X\n", (const void *)p, *p);
        p++;
    }

    return 0;
}
