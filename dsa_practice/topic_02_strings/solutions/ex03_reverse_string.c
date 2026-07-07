/* Reverse a mutable string in place. */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "algorithm";
    size_t n = strlen(s);
    for (size_t l = 0, r = n - 1; l < r; l++, r--) {
        char t = s[l];
        s[l] = s[r];
        s[r] = t;
    }
    puts(s);
    return 0;
}
