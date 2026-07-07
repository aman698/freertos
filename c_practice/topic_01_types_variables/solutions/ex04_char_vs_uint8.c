/*
 * ex04_char_vs_uint8.c — char may be signed; uint8_t is always unsigned
 * Key concept: use uint8_t for raw binary sensor / protocol bytes.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Sensor frame byte 0xFF — "full scale" reading */
    char     as_char  = (char)0xFF;
    uint8_t  as_u8    = 0xFF;

    printf("Raw byte 0xFF stored as:\n");
    printf("  char     -> printed as int: %d\n", (int)as_char);
    printf("  uint8_t  -> printed as int: %u\n", as_u8);

    if (as_char < 0) {
        printf("char is SIGNED on this compiler (0xFF reads as -1)\n");
    } else {
        printf("char is UNSIGNED on this compiler\n");
    }

    /* For embedded payloads, always prefer uint8_t */
    printf("Use uint8_t for I2C/SPI/UART payload bytes.\n");
    return 0;
}
