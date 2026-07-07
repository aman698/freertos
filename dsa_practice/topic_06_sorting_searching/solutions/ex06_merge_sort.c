/* Merge sort using a temporary array. */
#include <stdio.h>

static void merge_sort(int a[], int tmp[], int l, int r)
{
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort(a, tmp, l, m);
    merge_sort(a, tmp, m + 1, r);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = tmp[i];
}

int main(void)
{
    int a[] = {5, 2, 4, 1}, tmp[4];
    merge_sort(a, tmp, 0, 3);
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    putchar('\n');
    return 0;
}
