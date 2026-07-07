/*
 * ex08_struct_pointer.c — Struct member access via arrow operator
 * Key concept: ptr->field is shorthand for (*ptr).field.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t cr;
    uint32_t sr;
    uint32_t dr;
} uart_regs_t;

int main(void)
{
    uart_regs_t regs = { 0U, 0U, 0U };
    uart_regs_t *uart = &regs;

    uart->cr = 0x00002000UL;  /* UE bit — enable USART */
    uart->sr = 0x00000080UL;   /* TXE — transmit empty */
    uart->dr = (uint32_t)'A';

    printf("CR=0x%08lX SR=0x%08lX DR=0x%02lX ('%c')\n",
           (unsigned long)uart->cr,
           (unsigned long)uart->sr,
           (unsigned long)uart->dr,
           (char)uart->dr);

    return 0;
}
