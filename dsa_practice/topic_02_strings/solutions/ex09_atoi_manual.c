/* Convert decimal text to int. */
#include <stdio.h>

int main(void)
{
    const char *s = "-1234";
    int sign = 1, value = 0;
    size_t i = 0;
    if (s[i] == '-') {
        sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9') {
        value = value * 10 + (s[i] - '0');
        i++;
    }
    printf("value=%d\n", sign * value);
    return 0;
}
