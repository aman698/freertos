/* Count words separated by whitespace. */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    const char *s = "learn C data structures";
    bool in_word = false;
    int words = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            words++;
        }
    }
    printf("words=%d\n", words);
    return 0;
}
