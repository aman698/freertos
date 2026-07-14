/*
 * ex04_spi_shift_transfer.c — Simulate an SPI full-duplex byte exchange bit by bit
 * Key concept: SPI shifts MOSI out and MISO in simultaneously through paired shift registers.
 */
#include <stdint.h>
#include <stdio.h>

static uint8_t spi_transfer_byte(uint8_t mosi_byte, uint8_t miso_byte)
{
    uint8_t received = 0U;
    int8_t bit;

    printf("  clk  MOSI  MISO\n");
    for (bit = 7; bit >= 0; bit--) {
        uint8_t mosi_bit = (mosi_byte >> bit) & 1U;
        uint8_t miso_bit = (miso_byte >> bit) & 1U;

        received = (uint8_t)((received << 1U) | miso_bit);
        printf("  %2d    %u     %u\n", 8 - bit, mosi_bit, miso_bit);
    }
    return received;
}

int main(void)
{
    uint8_t master_out = 0xA5U; /* command byte MCU -> MCP2515 */
    uint8_t slave_out = 0x3CU;  /* status byte MCP2515 -> MCU */
    uint8_t master_in;

    printf("SPI transfer: MOSI=0x%02X MISO(expected)=0x%02X\n", master_out, slave_out);
    master_in = spi_transfer_byte(master_out, slave_out);
    printf("Master received on MISO: 0x%02X\n", master_in);
    return 0;
}
