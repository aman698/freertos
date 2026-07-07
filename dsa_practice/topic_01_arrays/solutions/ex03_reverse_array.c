/* Reverse an array in place using two pointers. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(a) / sizeof(a[0]);
    for (size_t l = 0, r = n - 1; l < r; l++, r--) {
        int t = a[l];
        a[l] = a[r];
        a[r] = t;
    }
    for (size_t i = 0; i < n; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
