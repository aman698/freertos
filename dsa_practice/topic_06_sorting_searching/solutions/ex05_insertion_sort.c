/* Insertion sort shifts larger elements right. */
#include <stdio.h>

int main(void)
{
    int a[] = {4, 3, 1, 2};
    for (int i = 1; i < 4; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
