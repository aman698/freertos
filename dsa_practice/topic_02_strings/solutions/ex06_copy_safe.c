/* Bounded string copy that always terminates. */
#include <stdio.h>

int main(void)
{
    const char *src = "hello world";
    char dst[6];
    size_t i = 0;
    while (i + 1 < sizeof(dst) && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    puts(dst);
    return 0;
}
