/*
 * ex02_uart_checksum_parity.c — XOR checksum and even-parity bit demo for a UART message
 * Key concept: XOR checksum catches simple transmission errors; parity flags single-bit corruption.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

static uint8_t uart_xor_checksum(const uint8_t *data, size_t len)
{
    uint8_t checksum = 0U;
    size_t i;

    if (data == NULL) {
        return 0U;
    }
    for (i = 0U; i < len; i++) {
        checksum ^= data[i];
    }
    return checksum;
}

static uint8_t uart_even_parity_bit(uint8_t byte)
{
    uint8_t parity = 0U;
    uint8_t i;

    for (i = 0U; i < 8U; i++) {
        parity ^= (byte >> i) & 1U;
    }
    return parity;
}

int main(void)
{
    const uint8_t message[] = { 0x41U, 0x54U, 0x2BU, 0x0DU }; /* "AT+" then CR */
    size_t i;
    uint8_t checksum;

    printf("Message bytes with even-parity bit:\n");
    for (i = 0U; i < sizeof(message); i++) {
        printf("  byte[%zu] = 0x%02X  parity_bit = %u\n", i, message[i], uart_even_parity_bit(message[i]));
    }

    checksum = uart_xor_checksum(message, sizeof(message));
    printf("XOR checksum over %zu bytes = 0x%02X\n", sizeof(message), checksum);
    return 0;
}
