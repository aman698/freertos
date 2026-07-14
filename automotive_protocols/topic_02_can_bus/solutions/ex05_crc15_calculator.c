/*
 * ex05_crc15_calculator.c - Compute the CAN CRC-15 checksum over a bitstream.
 * Key concept: CAN protects SOF..data with a 15-bit CRC using generator polynomial 0x4599.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_CRC15_POLY 0x4599U
#define CAN_CRC15_MASK 0x7FFFU

/* Illustrative bitwise CRC-15 matching the CAN generator polynomial
 * x^15 + x^14 + x^10 + x^8 + x^7 + x^4 + x^3 + 1 (non-reflected, init 0). */
static uint16_t can_crc15_bits(const uint8_t *bits, size_t len)
{
    uint16_t crc = 0U;

    for (size_t i = 0U; i < len; i++) {
        uint16_t bit     = (uint16_t)(bits[i] & 1U);
        uint16_t crcMsb  = (uint16_t)((crc >> 14) & 1U);
        uint16_t feedback = (uint16_t)(crcMsb ^ bit);

        crc = (uint16_t)((crc << 1) & CAN_CRC15_MASK);
        if (feedback != 0U) {
            crc ^= CAN_CRC15_POLY;
        }
    }
    return crc & CAN_CRC15_MASK;
}

static size_t can_bytes_to_msb_bits(const uint8_t *bytes, size_t byteLen, uint8_t *bits, size_t bitCap)
{
    size_t outLen = 0U;
    for (size_t i = 0U; i < byteLen; i++) {
        for (int8_t b = 7; b >= 0; b--) {
            if (outLen >= bitCap) {
                return outLen;
            }
            bits[outLen++] = (uint8_t)((bytes[i] >> b) & 1U);
        }
    }
    return outLen;
}

int main(void)
{
    /* Reference check vector, CRC-15/CAN catalogue: ASCII "123456789" -> 0x059E */
    const uint8_t message[] = "123456789";
    size_t msgLen = strlen((const char *)message);

    uint8_t bitBuf[128];
    size_t bitLen = can_bytes_to_msb_bits(message, msgLen, bitBuf, sizeof(bitBuf));

    uint16_t crc = can_crc15_bits(bitBuf, bitLen);
    printf("Message: \"%s\"\n", message);
    printf("Computed CRC-15 = 0x%04X\n", crc);
    printf("Expected (catalogue check value) = 0x059E\n");
    printf("Match: %s\n", (crc == 0x059EU) ? "YES" : "NO (illustrative implementation - verify bit order/init)");

    return 0;
}
