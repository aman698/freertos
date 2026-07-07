/*
 * ex10_scope_shadow.c — Inner block variable shadows outer
 * Key concept: inner declaration hides outer name within its block.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t pin = 5U;
    printf("Outer pin = %u (PA5 LD2)\n", pin);

    {
        uint8_t pin = 13U;  /* shadows outer — PC13 user button */
        printf("Inner pin = %u (PC13 button)\n", pin);
    }

    printf("Outer pin again = %u\n", pin);
    return 0;
}
