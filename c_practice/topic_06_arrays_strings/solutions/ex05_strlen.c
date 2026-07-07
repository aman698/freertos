/**
 * Topic 06 - Exercise 05: strlen and custom implementation
 * STM32 context: measuring command length before UART TX
 * Build: gcc ex05_strlen.c -o ex05 && ./ex05
 */
#include <stdio.h>
#include <string.h>

static size_t my_strlen(const char *s)
{
    size_t n = 0U;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

int main(void)
{
    const char *cmd = "AT+VER?\r\n";

    size_t lib_len = strlen(cmd);
    size_t my_len = my_strlen(cmd);

    printf("String: \"%s\"\n", cmd);
    printf("strlen()  = %zu\n", lib_len);
    printf("my_strlen = %zu\n", my_len);
    printf("Buffer need = %zu bytes (including NUL)\n", lib_len + 1U);
    return 0;
}
