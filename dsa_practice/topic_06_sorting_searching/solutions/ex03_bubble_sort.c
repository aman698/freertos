/* Bubble sort repeatedly swaps adjacent out-of-order elements. */
#include <stdio.h>

int main(void)
{
    int a[] = {5, 1, 4, 2};
    for (int pass = 0; pass < 3; pass++) {
        for (int i = 0; i < 3 - pass; i++) {
            if (a[i] > a[i + 1]) { int t = a[i]; a[i] = a[i + 1]; a[i + 1] = t; }
        }
    }
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
