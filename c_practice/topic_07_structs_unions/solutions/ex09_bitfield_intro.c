/*
 * ex09_bitfield_intro.c — Bitfields pack flags into integer storage
 * Key concept: bitfields specify field width in bits within struct.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t enable   : 1;
    uint32_t mode     : 2;
    uint32_t reserved : 5;
    uint32_t prescale : 8;
} ctrl_reg_t;

int main(void)
{
    ctrl_reg_t cr = { 0 };
    cr.enable = 1U;
    cr.mode = 2U;
    cr.prescale = 42U;

    printf("enable=%u mode=%u prescale=%u\n",
           cr.enable, cr.mode, cr.prescale);
    printf("sizeof(ctrl_reg_t) = %zu (typically 4 on 32-bit)\n", sizeof(cr));
    return 0;
}
