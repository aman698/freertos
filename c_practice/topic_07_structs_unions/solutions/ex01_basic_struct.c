/*
 * ex01_basic_struct.c — Basic struct definition and access
 * Key concept: struct groups related fields into one type.
 */
#include <stdint.h>
#include <stdio.h>

struct sensor_reading {
    uint16_t raw_adc;
    int16_t  temp_c;
    uint8_t  channel;
};

int main(void)
{
    struct sensor_reading s;
    s.raw_adc = 2048U;
    s.temp_c = 25;
    s.channel = 0U;

    printf("CH%u: raw=%u temp=%d C\n", s.channel, s.raw_adc, s.temp_c);
    return 0;
}
