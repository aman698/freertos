/*
 * ex02_static_local.c - Static locals keep their value between calls.
 * Key concept: static storage duration, block scope.
 */
#include <stdio.h>

static void poll_once(void)
{
    static int call_count = 0;
    call_count++;
    printf("call_count = %d\n", call_count);
}

int main(void)
{
    poll_once();
    poll_once();
    poll_once();
    return 0;
}
