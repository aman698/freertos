/**
 * Topic 06 - Exercise 02: Array decay to pointer
 * STM32 context: passing DMA buffer to processing function
 * Build: gcc ex02_array_decay.c -o ex02 && ./ex02
 */
#include <stdio.h>
#include <stdint.h>

static void print_buffer(uint8_t *buf, size_t len)
{
    /* sizeof(buf) here is pointer size, NOT array size */
    printf("Inside function: sizeof(buf)=%zu (pointer)\n", sizeof(buf));

    for (size_t i = 0U; i < len; i++) {
        printf("%02X ", buf[i]);
    }
    printf("\n");
}

int main(void)
{
    uint8_t dma_buf[4] = { 0xDE, 0xAD, 0xBE, 0xEF };

    printf("In main: sizeof(dma_buf)=%zu (full array)\n", sizeof(dma_buf));
    print_buffer(dma_buf, sizeof(dma_buf) / sizeof(dma_buf[0]));
    return 0;
}
