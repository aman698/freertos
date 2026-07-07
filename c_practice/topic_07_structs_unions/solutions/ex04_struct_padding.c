/*
 * ex04_struct_padding.c — Struct padding and alignment
 * Key concept: compiler inserts padding; sizeof may exceed field sum.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

typedef struct {
    uint8_t  flags;
    uint32_t timestamp;
    uint16_t value;
} padded_sample_t;

int main(void)
{
    printf("sizeof(padded_sample_t) = %zu bytes\n", sizeof(padded_sample_t));
    printf("  flags     offset = %zu\n", offsetof(padded_sample_t, flags));
    printf("  timestamp offset = %zu\n", offsetof(padded_sample_t, timestamp));
    printf("  value     offset = %zu\n", offsetof(padded_sample_t, value));
    printf("(Padding between flags and timestamp for uint32 alignment)\n");
    return 0;
}
