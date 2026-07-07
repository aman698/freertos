/* Count vowels in a string. */
#include <ctype.h>
#include <stdio.h>

static int is_vowel(char c)
{
    c = (char)tolower((unsigned char)c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(void)
{
    const char *s = "Data Structures";
    int count = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (is_vowel(s[i])) count++;
    }
    printf("vowels=%d\n", count);
    return 0;
}
