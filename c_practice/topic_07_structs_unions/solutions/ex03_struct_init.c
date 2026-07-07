/*
 * ex03_struct_init.c — Designated struct initializers
 * Key concept: C99 designated init sets fields by name.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t baudrate;
    uint8_t  databits;
    uint8_t  stopbits;
    uint8_t  parity;
} uart_config_t;

int main(void)
{
    uart_config_t cfg = {
        .baudrate = 115200UL,
        .databits = 8U,
        .stopbits = 1U,
        .parity   = 0U
    };

    printf("UART: %lu 8N1 (parity=%u)\n",
           (unsigned long)cfg.baudrate, cfg.parity);
    return 0;
}
