/*
 * ex08_kline_slow_init.c — Simulate the ISO 9141-2 K-Line 5-baud slow-init handshake
 * Key concept: the diagnostic tool bit-bangs address 0x33 at 5 baud before switching to normal UART speed.
 */
#include <stdint.h>
#include <stdio.h>

static uint8_t kline_invert(uint8_t byte)
{
    return (uint8_t)(~byte);
}

int main(void)
{
    const uint8_t init_address = 0x33U; /* 5-baud init byte, address 0x33 = all ECUs */
    const uint8_t sync_byte = 0x55U;    /* ECU sync pattern at normal UART baud */
    const uint8_t key_byte_1 = 0x08U;   /* KB1: example protocol keyword */
    const uint8_t key_byte_2 = 0x08U;   /* KB2: example protocol keyword */
    uint8_t inverted_kb2;
    uint8_t expected_inv_addr;

    printf("Tool  -> ECU : 0x%02X (5-baud init address)\n", init_address);
    printf("ECU   -> Tool: 0x%02X (sync byte)\n", sync_byte);
    printf("ECU   -> Tool: 0x%02X (key byte 1)\n", key_byte_1);
    printf("ECU   -> Tool: 0x%02X (key byte 2)\n", key_byte_2);

    inverted_kb2 = kline_invert(key_byte_2);
    expected_inv_addr = kline_invert(init_address);

    printf("Tool  -> ECU : 0x%02X (inverted key byte 2)\n", inverted_kb2);
    printf("ECU   -> Tool: 0x%02X (inverted address)\n", expected_inv_addr);
    printf("Slow-init complete, switching to normal UART framing at negotiated baud\n");
    return 0;
}
