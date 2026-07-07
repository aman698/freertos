/*
 * ex02_pass_by_value.c — Pass by value does not modify caller
 * Key concept: function receives a copy; original variable unchanged.
 */
#include <stdint.h>
#include <stdio.h>

static void increment_copy(uint8_t value)
{
    value++;
    printf("  inside increment_copy: value=%u\n", value);
}

int main(void)
{
    uint8_t counter = 10U;

    printf("Before: counter=%u\n", counter);
    increment_copy(counter);
    printf("After:  counter=%u (unchanged)\n", counter);

    return 0;
}
