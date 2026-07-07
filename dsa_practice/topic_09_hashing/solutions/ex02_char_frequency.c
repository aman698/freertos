/* Character frequency table. */
#include <stdio.h>

int main(void)
{
    const char *s = "banana";
    int freq[256] = {0};
    for (size_t i = 0; s[i] != '\0'; i++) freq[(unsigned char)s[i]]++;
    printf("a=%d b=%d n=%d\n", freq['a'], freq['b'], freq['n']);
    return 0;
}
