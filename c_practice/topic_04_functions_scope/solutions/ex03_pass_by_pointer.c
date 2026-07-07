/*
 * ex03_pass_by_pointer.c — Modify caller data through pointer
 * Key concept: pass address so function can update caller's variable.
 */
#include <stdint.h>
#include <stdio.h>

static void increment_via_ptr(uint8_t *value)
{
    if (value != NULL) {
        (*value)++;
    }
}

int main(void)
{
    uint8_t counter = 10U;

    printf("Before: counter=%u\n", counter);
    increment_via_ptr(&counter);
    printf("After:  counter=%u (updated)\n", counter);

    return 0;
}
