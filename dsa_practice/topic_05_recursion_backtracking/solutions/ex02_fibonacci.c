/* Recursive Fibonacci, clear but exponential. */
#include <stdio.h>

static int fib(int n) { return (n <= 1) ? n : fib(n - 1) + fib(n - 2); }

int main(void)
{
    printf("fib(6)=%d\n", fib(6));
    return 0;
}
