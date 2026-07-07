/*
 * ex11_error_recovery.c - Fault state requires explicit reset.
 * Key concept: safe systems do not leave fault automatically.
 */
#include <stdio.h>

typedef enum { ST_OK, ST_FAULT } State_t;

int main(void)
{
    State_t state = ST_OK;
    puts("running");

    state = ST_FAULT;
    puts("fault latched");

    state = ST_OK;
    puts("reset complete, back to OK");
    return 0;
}
