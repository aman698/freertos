/* Check balanced parentheses with a stack. */
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    const char *s = "(()())";
    int stack = 0;
    bool ok = true;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') stack++;
        if (s[i] == ')' && --stack < 0) ok = false;
    }
    if (stack != 0) ok = false;
    printf("balanced=%s\n", ok ? "yes" : "no");
    return 0;
}
