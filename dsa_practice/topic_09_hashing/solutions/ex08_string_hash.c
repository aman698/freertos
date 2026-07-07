/* Polynomial rolling-style string hash. */
#include <stdio.h>

int main(void)
{
    const char *s = "abc";
    unsigned hash = 0;
    for (size_t i = 0; s[i] != '\0'; i++) hash = hash * 31U + (unsigned char)s[i];
    printf("hash=%u\n", hash);
    return 0;
}
