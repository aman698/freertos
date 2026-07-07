/* Manual strlen implementation. */
#include <stdio.h>

int main(void)
{
    const char *s = "embedded";
    size_t len = 0;
    while (s[len] != '\0') len++;
    printf("len=%zu\n", len);
    return 0;
}
