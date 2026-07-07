/**
 * Topic 06 - Exercise 07: snprintf for sensor telemetry
 * STM32 context: format USART debug line
 * Build: gcc ex07_snprintf_sensor.c -o ex07 && ./ex07
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    char line[32];
    int16_t temp_c_x10 = 235;   /* 23.5 C */
    uint8_t humidity = 62U;

    int n = snprintf(line, sizeof(line), "T=%d.%dC H=%u%%\r\n",
                     temp_c_x10 / 10, temp_c_x10 % 10, humidity);

    if (n < 0) {
        printf("snprintf error\n");
        return 1;
    }
    if ((size_t)n >= sizeof(line)) {
        printf("Truncated (%d chars needed)\n", n);
    }

    printf("TX: %s", line);
    printf("Length=%d  BufSize=%zu\n", n, sizeof(line));
    return 0;
}
