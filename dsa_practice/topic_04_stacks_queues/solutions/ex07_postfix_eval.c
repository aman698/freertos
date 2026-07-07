/* Evaluate postfix expression with single-digit operands. */
#include <stdio.h>

int main(void)
{
    const char *expr = "23+4*";
    int st[8], top = 0;
    for (size_t i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c >= '0' && c <= '9') st[top++] = c - '0';
        else {
            int b = st[--top], a = st[--top];
            st[top++] = (c == '+') ? a + b : a * b;
        }
    }
    printf("value=%d\n", st[0]);
    return 0;
}
