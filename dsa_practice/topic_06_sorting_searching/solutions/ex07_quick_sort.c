/* Quick sort with Lomuto partition. */
#include <stdio.h>

static void quick_sort(int a[], int l, int r)
{
    if (l >= r) return;
    int pivot = a[r], i = l;
    for (int j = l; j < r; j++) {
        if (a[j] < pivot) { int t = a[i]; a[i] = a[j]; a[j] = t; i++; }
    }
    int t = a[i]; a[i] = a[r]; a[r] = t;
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

int main(void)
{
    int a[] = {4, 1, 5, 2};
    quick_sort(a, 0, 3);
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
