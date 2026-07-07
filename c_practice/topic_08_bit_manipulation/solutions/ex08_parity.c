/*
 * ex08_parity.c — Compute even parity bit for UART frame
 * Key concept: XOR all bits to get parity; append for error detection.
 */
#include <stdint.h>
#include <stdio.h>

static uint8_t even_parity(uint8_t data)
{
    uint8_t p = 0U;
    for (uint8_t i = 0U; i < 8U; i++) {
        p ^= (data >> i) & 1U;
    }
    return p;
}

int main(void)
{
    uint8_t bytes[] = { 0x00, 0x55, 0xFF, 0xA5 };

    for (size_t i = 0U; i < sizeof(bytes); i++) {
        printf("0x%02X -> even parity bit = %u\n", bytes[i], even_parity(bytes[i]));
    }
    return 0;
}
