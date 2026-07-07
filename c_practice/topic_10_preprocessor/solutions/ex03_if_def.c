/*
 * ex03_if_def.c — #ifdef enables optional debug code
 * Key concept: define DEBUG to compile extra logging paths.
 */
#include <stdint.h>
#include <stdio.h>

#define DEBUG 1

static void sensor_read(void)
{
#ifdef DEBUG
    printf("[DEBUG] ADC read start\n");
#endif
    printf("ADC value = 2048\n");
#ifdef DEBUG
    printf("[DEBUG] ADC read done\n");
#endif
}

int main(void)
{
    sensor_read();
    return 0;
}
