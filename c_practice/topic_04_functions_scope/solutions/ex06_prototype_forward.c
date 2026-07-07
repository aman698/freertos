/*
 * ex06_prototype_forward.c — Forward declarations enable mutual calls
 * Key concept: prototype tells compiler signature before definition.
 */
#include <stdint.h>
#include <stdio.h>

static int process_b(int x);  /* forward declaration */

static int process_a(int x)
{
    if (x > 0) {
        return process_b(x - 1);
    }
    return 0;
}

static int process_b(int x)
{
    return process_a(x) + 1;
}

int main(void)
{
    printf("process_a(3) = %d\n", process_a(3));
    return 0;
}
