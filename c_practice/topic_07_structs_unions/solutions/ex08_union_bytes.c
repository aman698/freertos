/*
 * ex08_union_bytes.c — Access 32-bit register as individual bytes
 * Key concept: union enables byte-wise inspection of word data.
 */
#include <stdint.h>
#include <stdio.h>

typedef union {
    uint32_t reg;
    struct {
        uint8_t b0;
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
    } bytes;
} reg_bytes_t;

int main(void)
{
    reg_bytes_t r;
    r.reg = 0xAABBCCDDUL;

    printf("reg = 0x%08lX\n", (unsigned long)r.reg);
    printf("bytes: %02X %02X %02X %02X\n",
           r.bytes.b0, r.bytes.b1, r.bytes.b2, r.bytes.b3);
    return 0;
}
