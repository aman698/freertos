/* Rotate an array left by one position. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 3, 4};
    size_t n = sizeof(a) / sizeof(a[0]);
    int first = a[0];
    for (size_t i = 1; i < n; i++) a[i - 1] = a[i];
    a[n - 1] = first;
    for (size_t i = 0; i < n; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
