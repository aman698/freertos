/* Remove duplicates from a sorted array in place. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 1, 2, 2, 3, 4, 4};
    size_t n = sizeof(a) / sizeof(a[0]);
    size_t write = 0;
    for (size_t read = 0; read < n; read++) {
        if (write == 0 || a[read] != a[write - 1]) {
            a[write++] = a[read];
        }
    }
    for (size_t i = 0; i < write; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
