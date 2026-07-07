/*
 * ex05_heap_malloc_free.c - Allocate, use, and free heap memory.
 * Key concept: ownership must include a matching free.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 8U;
    uint8_t *buffer = malloc(count * sizeof(buffer[0]));
    if (buffer == NULL) {
        puts("malloc failed");
        return 1;
    }

    for (size_t i = 0U; i < count; i++) {
        buffer[i] = (uint8_t)(i + 10U);
        printf("%u ", buffer[i]);
    }
    putchar('\n');

    free(buffer);
    buffer = NULL;
    return 0;
}
