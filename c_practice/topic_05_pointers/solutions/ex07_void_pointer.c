/*
 * ex07_void_pointer.c — Generic void* requires cast before use
 * Key concept: void* holds any address; cast to typed pointer to dereference.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void mem_copy(void *dst, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    for (size_t i = 0U; i < n; i++) {
        d[i] = s[i];
    }
}

int main(void)
{
    const uint8_t src[] = { 0xDE, 0xAD, 0xBE, 0xEF };
    uint8_t dst[4] = { 0 };

    mem_copy(dst, src, sizeof(src));

    printf("Copied: ");
    for (size_t i = 0U; i < sizeof(dst); i++) {
        printf("%02X ", dst[i]);
    }
    printf("\n");

    return 0;
}
