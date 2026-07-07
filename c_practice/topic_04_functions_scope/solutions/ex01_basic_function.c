/*
 * ex01_basic_function.c — Basic function definition and call
 * Key concept: functions encapsulate reusable logic with parameters and return.
 */
#include <stdint.h>
#include <stdio.h>

static int32_t celsius_to_fahrenheit(int32_t c)
{
    return (c * 9) / 5 + 32;
}

int main(void)
{
    int32_t temps[] = { 0, 25, 100 };
    for (size_t i = 0U; i < sizeof(temps) / sizeof(temps[0]); i++) {
        printf("%ld C = %ld F\n",
               (long)temps[i], (long)celsius_to_fahrenheit(temps[i]));
    }
    return 0;
}
