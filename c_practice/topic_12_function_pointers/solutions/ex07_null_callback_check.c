/*
 * ex07_null_callback_check.c - Never call a missing callback.
 * Key concept: validate function pointers before use.
 */
#include <stdio.h>

typedef void (*Callback_t)(void);

static void run_optional(Callback_t cb)
{
    if (cb == NULL) {
        puts("callback not installed");
        return;
    }
    cb();
}

int main(void)
{
    run_optional(NULL);
    return 0;
}
