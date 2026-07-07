/*
 * ex08_macro_pitfalls.c — Macro side effects when args evaluated twice
 * Key concept: use inline functions or careful macros with do-while(0).
 */
#include <stdint.h>
#include <stdio.h>

#define SQUARE_BAD(x) ((x) * (x))
#define SQUARE_GOOD(x) ({ typeof(x) _x = (x); _x * _x; })  /* GCC statement expr */

static int call_count;

static int expensive(void)
{
    call_count++;
    return 3;
}

int main(void)
{
    call_count = 0;
    int r1 = SQUARE_BAD(expensive());  /* expensive() called twice! */
    printf("SQUARE_BAD: result=%d calls=%d\n", r1, call_count);

    call_count = 0;
    int r2 = SQUARE_GOOD(expensive());
    printf("SQUARE_GOOD: result=%d calls=%d\n", r2, call_count);

    return 0;
}
