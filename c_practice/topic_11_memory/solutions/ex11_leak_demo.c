/*
 * ex11_leak_demo.c - Make ownership visible to prevent leaks.
 * Key concept: the function that owns heap memory must release it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *make_message(const char *text)
{
    size_t len = strlen(text) + 1U;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, text, len);
    }
    return copy;
}

int main(void)
{
    char *msg = make_message("owned heap message");
    if (msg == NULL) {
        return 1;
    }

    puts(msg);
    free(msg);
    msg = NULL;
    return 0;
}
