/*
 * ex07_recursion_factorial.c — Recursive factorial
 * Key concept: function calls itself with smaller argument until base case.
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t factorial(uint8_t n)
{
    if (n <= 1U) {
        return 1U;
    }
    return (uint32_t)n * factorial(n - 1U);
}

int main(void)
{
    printf("5! = %lu\n", (unsigned long)factorial(5));
    printf("0! = %lu\n", (unsigned long)factorial(0));
    return 0;
}
