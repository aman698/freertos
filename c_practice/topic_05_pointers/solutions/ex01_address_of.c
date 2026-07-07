/*
 * ex01_address_of.c — Address-of operator &
 * Key concept: & returns the memory address of a variable.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint32_t tick = 0x12345678UL;
    uint32_t *tick_ptr = &tick;

    printf("tick value  = 0x%08lX\n", (unsigned long)tick);
    printf("tick address = %p\n", (void *)&tick);
    printf("via pointer  = 0x%08lX\n", (unsigned long)(*tick_ptr));

    return 0;
}
