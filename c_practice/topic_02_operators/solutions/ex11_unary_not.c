/*
 * ex11_unary_not.c — Logical ! vs bitwise ~
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t flag = 0U;
    uint8_t mask = 0x0FU;

    printf("!flag=%d\n", !flag);
    printf("~mask=0x%02X\n", (unsigned)(~mask & 0xFFU));
    return 0;
}
