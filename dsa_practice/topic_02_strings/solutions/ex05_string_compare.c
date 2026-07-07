/* Manual strcmp-style comparison. */
#include <stdio.h>

int main(void)
{
    const char *a = "abc";
    const char *b = "abd";
    size_t i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]) i++;
    printf("compare=%d\n", (unsigned char)a[i] - (unsigned char)b[i]);
    return 0;
}
