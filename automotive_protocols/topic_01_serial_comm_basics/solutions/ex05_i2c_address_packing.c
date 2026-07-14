/*
 * ex05_i2c_address_packing.c — Pack a 7-bit I2C address and R/W bit into the wire byte
 * Key concept: the address byte on the wire is (7-bit address << 1) | R/W bit.
 */
#include <stdint.h>
#include <stdio.h>

#define I2C_WRITE 0U
#define I2C_READ  1U

static uint8_t i2c_pack_address(uint8_t addr7, uint8_t rw)
{
    return (uint8_t)((addr7 << 1U) | (rw & 1U));
}

static void i2c_unpack_address(uint8_t wire_byte, uint8_t *addr7, uint8_t *rw)
{
    if (addr7 == NULL || rw == NULL) {
        return;
    }
    *addr7 = (wire_byte >> 1U) & 0x7FU;
    *rw = wire_byte & 1U;
}

int main(void)
{
    uint8_t eeprom_addr = 0x50U; /* common I2C EEPROM address */
    uint8_t wire_write = i2c_pack_address(eeprom_addr, I2C_WRITE);
    uint8_t wire_read = i2c_pack_address(eeprom_addr, I2C_READ);
    uint8_t decoded_addr;
    uint8_t decoded_rw;

    printf("7-bit address 0x%02X -> write byte 0x%02X, read byte 0x%02X\n", eeprom_addr, wire_write, wire_read);

    i2c_unpack_address(wire_read, &decoded_addr, &decoded_rw);
    printf("Decoded from 0x%02X: address=0x%02X rw=%s\n",
           wire_read, decoded_addr, (decoded_rw == I2C_READ) ? "READ" : "WRITE");
    return 0;
}
