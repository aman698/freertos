/* Generate all binary strings of length 3. */
#include <stdio.h>

static void gen(char s[], int i, int n)
{
    if (i == n) {
        s[n] = '\0';
        puts(s);
        return;
    }
    s[i] = '0'; gen(s, i + 1, n);
    s[i] = '1'; gen(s, i + 1, n);
}

int main(void)
{
    char s[4];
    gen(s, 0, 3);
    return 0;
}
