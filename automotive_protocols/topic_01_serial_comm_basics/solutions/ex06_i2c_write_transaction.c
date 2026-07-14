/*
 * ex06_i2c_write_transaction.c — Simulate an I2C write transaction with per-byte ACK/NACK
 * Key concept: every byte on I2C (address or data) is followed by a 9th ACK/NACK clock from the receiver.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
    I2C_ACK = 0,
    I2C_NACK = 1
} i2c_response_t;

static i2c_response_t i2c_send_byte(uint8_t byte, const char *role)
{
    i2c_response_t response;

    if (role == NULL) {
        role = "UNKNOWN";
    }
    /* Simulate: every byte is acknowledged except a byte value used here to model a full buffer. */
    response = (byte == 0xFFU) ? I2C_NACK : I2C_ACK;
    printf("  %-12s 0x%02X -> %s\n", role, byte, (response == I2C_ACK) ? "ACK" : "NACK");
    return response;
}

int main(void)
{
    const uint8_t device_addr_write = 0xA0U; /* 7-bit 0x50 << 1 | write */
    const uint8_t data[] = { 0x00U, 0x10U, 0xFFU }; /* last byte simulates a NACK */
    size_t i;

    printf("START\n");
    if (i2c_send_byte(device_addr_write, "ADDR+W") == I2C_ACK) {
        for (i = 0U; i < sizeof(data); i++) {
            if (i2c_send_byte(data[i], "DATA") == I2C_NACK) {
                printf("  slave NACKed, master aborts write\n");
                break;
            }
        }
    } else {
        printf("  slave not present, aborting\n");
    }
    printf("STOP\n");
    return 0;
}
