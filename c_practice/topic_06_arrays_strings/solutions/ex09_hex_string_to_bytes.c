/**
 * Topic 06 - Exercise 09: Hex ASCII string to bytes
 * STM32 context: decode hex firmware chunk from UART
 * Build: gcc ex09_hex_string_to_bytes.c -o ex09 && ./ex09
 */
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

static int hex_nibble(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

static int hex_string_to_bytes(const char *hex, uint8_t *out, size_t out_max, size_t *out_len)
{
    size_t i = 0U;
    size_t hex_len = 0U;

    while (hex[hex_len] != '\0') {
        hex_len++;
    }
    if ((hex_len % 2U) != 0U) {
        return -1;
    }

    *out_len = hex_len / 2U;
    if (*out_len > out_max) {
        return -2;
    }

    for (i = 0U; i < *out_len; i++) {
        int hi = hex_nibble(hex[i * 2U]);
        int lo = hex_nibble(hex[i * 2U + 1U]);
        if (hi < 0 || lo < 0) {
            return -3;
        }
        out[i] = (uint8_t)((hi << 4) | lo);
    }
    return 0;
}

int main(void)
{
    const char *hex = "A5F0";
    uint8_t bytes[4];
    size_t len = 0U;

    if (hex_string_to_bytes(hex, bytes, sizeof(bytes), &len) == 0) {
        printf("Hex \"%s\" -> %zu bytes:", hex, len);
        for (size_t i = 0U; i < len; i++) {
            printf(" %02X", bytes[i]);
        }
        printf("\n");
    }
    return 0;
}
