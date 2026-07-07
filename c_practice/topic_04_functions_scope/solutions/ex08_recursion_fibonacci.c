/*
 * ex08_recursion_fibonacci.c — Recursive Fibonacci sequence
 * Key concept: watch stack depth — deep recursion is risky on MCUs.
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t fib(uint8_t n)
{
    if (n <= 1U) {
        return (uint32_t)n;
    }
    return fib(n - 1U) + fib(n - 2U);
}

int main(void)
{
    printf("Fibonacci 0..6:\n");
    for (uint8_t i = 0U; i <= 6U; i++) {
        printf("  fib(%u) = %lu\n", i, (unsigned long)fib(i));
    }
    return 0;
}
