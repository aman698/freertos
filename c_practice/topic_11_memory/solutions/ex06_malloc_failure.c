/*
 * ex06_malloc_failure.c - Always check malloc result before use.
 * Key concept: NULL means no memory was returned.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t *make_buffer(size_t bytes)
{
    if (bytes > 1024U) {
        return NULL; /* Simulated firmware limit. */
    }
    return malloc(bytes);
}

int main(void)
{
    uint8_t *buf = make_buffer(2048U);
    if (buf == NULL) {
        puts("allocation rejected safely");
        return 0;
    }

    free(buf);
    return 0;
}
