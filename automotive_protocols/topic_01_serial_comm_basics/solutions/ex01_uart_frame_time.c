/*
 * ex01_uart_frame_time.c — Compute UART frame and byte time from serial settings
 * Key concept: total frame time = (start + data + parity + stop bits) / baud rate.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t parity_bits; /* 0 = none, 1 = odd or even */
    uint8_t stop_bits;
    const char *label;
} uart_config_t;

static double uart_bit_time_us(uint32_t baud_rate)
{
    return 1000000.0 / (double)baud_rate;
}

static double uart_frame_time_us(const uart_config_t *cfg)
{
    uint32_t total_bits;

    if (cfg == NULL) {
        return 0.0;
    }
    total_bits = 1U + (uint32_t)cfg->data_bits + (uint32_t)cfg->parity_bits + (uint32_t)cfg->stop_bits;
    return (double)total_bits * uart_bit_time_us(cfg->baud_rate);
}

int main(void)
{
    const uart_config_t configs[] = {
        { 9600U, 8U, 0U, 1U, "9600 8N1 (typical debug console)" },
        { 10400U, 8U, 1U, 1U, "10400 8E1 (ISO 9141-2 K-Line)" },
        { 115200U, 8U, 0U, 1U, "115200 8N1 (fast diagnostic tool)" },
    };
    size_t i;

    for (i = 0U; i < sizeof(configs) / sizeof(configs[0]); i++) {
        double bit_us = uart_bit_time_us(configs[i].baud_rate);
        double frame_us = uart_frame_time_us(&configs[i]);

        printf("%-40s bit=%.2f us  frame(byte)=%.2f us\n", configs[i].label, bit_us, frame_us);
    }
    return 0;
}
