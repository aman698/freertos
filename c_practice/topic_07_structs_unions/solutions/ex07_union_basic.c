/*
 * ex07_union_basic.c — Union members share same storage
 * Key concept: only one union member is active at a time.
 */
#include <stdint.h>
#include <stdio.h>

typedef union {
    uint32_t word;
    uint16_t half[2];
    uint8_t  byte[4];
} word_view_t;

int main(void)
{
    word_view_t u;
    u.word = 0x12345678UL;

    printf("word = 0x%08lX\n", (unsigned long)u.word);
    printf("half[0]=0x%04X half[1]=0x%04X\n", u.half[0], u.half[1]);
    printf("(Byte order depends on CPU endianness)\n");
    return 0;
}
