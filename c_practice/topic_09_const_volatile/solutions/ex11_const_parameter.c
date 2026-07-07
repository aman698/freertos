/*
 * ex11_const_parameter.c — const pointer param for read-only input
 * Key concept: const uint8_t* buf promises function won't modify buffer.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

static uint8_t checksum(const uint8_t *data, size_t len)
{
    uint8_t sum = 0U;
    for (size_t i = 0U; i < len; i++) {
        sum += data[i];
    }
    return sum;
}

int main(void)
{
    const uint8_t frame[] = { 0x01, 0x02, 0x03, 0x04 };
    printf("Checksum = 0x%02X\n", checksum(frame, sizeof(frame)));
    return 0;
}
