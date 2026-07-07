/*
 * ex11_pointer_comparison.c — Compare pointers for loop bounds
 * Key concept: pointers to same array can be compared with < > ==.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const char msg[] = "HELLO";
    const char *p = msg;
    const char *end = msg + sizeof(msg) - 1U;  /* exclude null terminator */

    printf("Chars: ");
    while (p < end) {
        printf("%c ", *p);
        p++;
    }
    printf("\n");

    return 0;
}
