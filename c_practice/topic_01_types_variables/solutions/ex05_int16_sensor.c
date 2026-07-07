/*
 * ex05_int16_sensor.c — Signed 16-bit temperature from raw ADC/counts
 * Key concept: int16_t holds negative sensor values in two's complement.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Simulated I2C temperature register: 0xFFF4 = -12 in int16_t */
    uint16_t raw_u16 = 0xFFF4;
    int16_t  temp_c  = (int16_t)raw_u16;

    printf("Raw register: 0x%04X\n", raw_u16);
    printf("Temperature:  %d C\n", temp_c);

    /* Another reading: +25 C */
    int16_t temp2 = 25;
    printf("Room temp:    %d C\n", temp2);
    printf("int16_t range: %d to %d\n", INT16_MIN, INT16_MAX);

    return 0;
}
