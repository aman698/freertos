/**
 * Topic 06 - Exercise 06: Safe bounded string copy
 * STM32 context: copy user command into fixed RX buffer
 * Build: gcc ex06_safe_strcpy.c -o ex06 && ./ex06
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int safe_strcpy(char *dst, size_t dst_size, const char *src)
{
    size_t i;

    if (dst == NULL || src == NULL || dst_size == 0U) {
        return -1;
    }

    for (i = 0U; i < dst_size - 1U && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';

    return (src[i] != '\0') ? 1 : 0;  /* 1 = truncated */
}

int main(void)
{
    char rx_buf[8];
    const char *long_cmd = "LED_ON_HIGH";
    const char *short_cmd = "OK";

    int trunc = safe_strcpy(rx_buf, sizeof(rx_buf), long_cmd);
    printf("Copy long: \"%s\" trunc=%d\n", rx_buf, trunc);

    trunc = safe_strcpy(rx_buf, sizeof(rx_buf), short_cmd);
    printf("Copy short: \"%s\" trunc=%d\n", rx_buf, trunc);
    return 0;
}
