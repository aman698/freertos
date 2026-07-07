/*
 * ex05_stringify.c — # operator converts macro arg to string literal
 * Key concept: #x in macro becomes "x" after substitution.
 */
#include <stdint.h>
#include <stdio.h>

#define STR(x) #x
#define LOG_VAR(v) printf(#v " = %d\n", (int)(v))

int main(void)
{
    int temp_c = 25;
    LOG_VAR(temp_c);
    printf("Pin name string: %s\n", STR(PA5));
    return 0;
}
