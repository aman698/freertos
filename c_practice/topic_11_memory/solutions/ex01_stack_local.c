/*
 * ex01_stack_local.c - Local variables live only for one function call.
 * Key concept: automatic locals are stored in the current stack frame.
 */
#include <stdio.h>

static void poll_once(void)
{
    int local_count = 0;
    local_count++;
    printf("local_count = %d\n", local_count);
}

int main(void)
{
    poll_once();
    poll_once();
    poll_once();
    return 0;
}
