/*
 * ex05_struct_array.c — Array of structs for multi-channel data
 * Key concept: struct arrays store one record per sensor/channel.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t  id;
    uint16_t raw;
} channel_t;

int main(void)
{
    channel_t channels[] = {
        { 0, 1000 }, { 1, 1100 }, { 2, 950 }, { 3, 1200 }
    };
    const size_t n = sizeof(channels) / sizeof(channels[0]);

    for (size_t i = 0U; i < n; i++) {
        printf("CH%u raw=%u\n", channels[i].id, channels[i].raw);
    }
    return 0;
}
