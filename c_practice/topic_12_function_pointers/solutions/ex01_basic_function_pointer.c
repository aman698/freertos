/*
 * ex01_basic_function_pointer.c - Store a function address and call it.
 * Key concept: function pointer declaration syntax.
 */
#include <stdio.h>

static void led_on(void)
{
    puts("LED ON");
}

int main(void)
{
    void (*action)(void) = led_on;
    action();
    return 0;
}
