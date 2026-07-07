/* Generate permutations by swapping. */
#include <stdio.h>
#include <string.h>

static void swap(char *a, char *b) { char t = *a; *a = *b; *b = t; }

static void permute(char s[], int l, int r)
{
    if (l == r) {
        puts(s);
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(&s[l], &s[i]);
        permute(s, l + 1, r);
        swap(&s[l], &s[i]);
    }
}

int main(void)
{
    char s[] = "abc";
    permute(s, 0, (int)strlen(s) - 1);
    return 0;
}
