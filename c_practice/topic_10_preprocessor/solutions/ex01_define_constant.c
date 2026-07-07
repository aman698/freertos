/*
 * ex01_define_constant.c — #define for compile-time constants
 * Key concept: #define creates text replacement before compilation.
 */
#include <stdint.h>
#include <stdio.h>

#define LED_PIN        5U
#define SYSCLK_HZ      84000000UL
#define UART_BAUD      115200UL

int main(void)
{
    printf("LED=PA%u SYSCLK=%lu Hz UART=%lu baud\n",
           LED_PIN, (unsigned long)SYSCLK_HZ, (unsigned long)UART_BAUD);
    return 0;
}
