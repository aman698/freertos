/* Find first occurrence of a character. */
#include <stdio.h>

int main(void)
{
    const char *s = "firmware";
    char target = 'w';
    int index = -1;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == target) {
            index = (int)i;
            break;
        }
    }
    printf("index=%d\n", index);
    return 0;
}
