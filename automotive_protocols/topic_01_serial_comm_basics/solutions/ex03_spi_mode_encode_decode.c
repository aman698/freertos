/*
 * ex03_spi_mode_encode_decode.c — Pack/unpack SPI CPOL and CPHA into a mode number
 * Key concept: SPI mode 0-3 encodes clock idle polarity and sampling edge as (CPOL<<1)|CPHA.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t cpol;
    uint8_t cpha;
} spi_mode_bits_t;

static uint8_t spi_encode_mode(spi_mode_bits_t bits)
{
    return (uint8_t)((bits.cpol << 1U) | bits.cpha);
}

static spi_mode_bits_t spi_decode_mode(uint8_t mode)
{
    spi_mode_bits_t bits;

    bits.cpol = (mode >> 1U) & 1U;
    bits.cpha = mode & 1U;
    return bits;
}

static void spi_print_effect(uint8_t mode)
{
    spi_mode_bits_t bits = spi_decode_mode(mode);
    const char *idle = (bits.cpol == 0U) ? "idle LOW" : "idle HIGH";
    const char *edge = (bits.cpha == 0U) ? "sample on 1st (leading) edge" : "sample on 2nd (trailing) edge";

    printf("Mode %u: CPOL=%u CPHA=%u -> clock %s, %s\n", mode, bits.cpol, bits.cpha, idle, edge);
}

int main(void)
{
    uint8_t mode;
    spi_mode_bits_t sensor_bits = { 1U, 1U }; /* CPOL=1, CPHA=1 */
    uint8_t encoded;

    for (mode = 0U; mode < 4U; mode++) {
        spi_print_effect(mode);
    }

    encoded = spi_encode_mode(sensor_bits);
    printf("Sensor requires CPOL=1 CPHA=1 -> encoded mode = %u\n", encoded);
    return 0;
}
