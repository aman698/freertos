/*
 * ex12_embedded_buffer_ptr.c — UART TX using pointer + length
 * Key concept: drivers take (uint8_t *buf, size_t len) for DMA/UART.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

static void uart_transmit(const uint8_t *data, size_t len)
{
    if (data == NULL) {
        return;
    }
    printf("UART TX (%zu bytes): ", len);
    for (size_t i = 0U; i < len; i++) {
        putchar((char)data[i]);
    }
    printf("\n");
}

int main(void)
{
    const uint8_t packet[] = { 'A', 'T', '+', 'G', 'M', 'R', '\r', '\n' };
    uart_transmit(packet, sizeof(packet));
    return 0;
}
