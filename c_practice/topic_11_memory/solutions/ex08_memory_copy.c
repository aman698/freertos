/*
 * ex08_memory_copy.c - Copy fixed-size byte data with memcpy.
 * Key concept: use sizeof destination when copying complete objects.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    uint8_t src[4] = {0xAAU, 0x55U, 0x12U, 0x34U};
    uint8_t dst[4] = {0U};

    memcpy(dst, src, sizeof(dst));
    printf("dst: %02X %02X %02X %02X\n", dst[0], dst[1], dst[2], dst[3]);
    return 0;
}
