/*
 * ex02_typedef_callback.c - Typedef makes callbacks readable.
 * Key concept: typedef for a function pointer type.
 */
#include <stdio.h>

typedef void (*Callback_t)(void);

static void on_ready(void)
{
    puts("system ready");
}

int main(void)
{
    Callback_t cb = on_ready;
    cb();
    return 0;
}
