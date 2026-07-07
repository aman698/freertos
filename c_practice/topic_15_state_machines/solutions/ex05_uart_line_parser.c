/*
 * ex05_uart_line_parser.c - Collect characters until newline.
 * Key concept: parser state tracks whether a line is being built.
 */
#include <stdio.h>

#define BUF_LEN 16U

int main(void)
{
    const char *rx = "TEMP=25\n";
    char line[BUF_LEN];
    size_t len = 0U;

    for (size_t i = 0U; rx[i] != '\0'; i++) {
        if (rx[i] == '\n') {
            line[len] = '\0';
            printf("line: %s\n", line);
            len = 0U;
        } else if (len + 1U < BUF_LEN) {
            line[len++] = rx[i];
        }
    }
    return 0;
}
