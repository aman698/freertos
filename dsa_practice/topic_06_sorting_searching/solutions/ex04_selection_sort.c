/* Selection sort chooses the minimum for each position. */
#include <stdio.h>

int main(void)
{
    int a[] = {3, 1, 4, 2};
    for (int i = 0; i < 3; i++) {
        int min = i;
        for (int j = i + 1; j < 4; j++) if (a[j] < a[min]) min = j;
        int t = a[i]; a[i] = a[min]; a[min] = t;
    }
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
