/* Check whether a string is a palindrome. */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *s = "level";
    bool ok = true;
    for (size_t l = 0, r = strlen(s) - 1; l < r; l++, r--) {
        if (s[l] != s[r]) ok = false;
    }
    printf("palindrome=%s\n", ok ? "yes" : "no");
    return 0;
}
