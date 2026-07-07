/* Sum array recursively from index i to end. */
#include <stdio.h>

static int sum(const int a[], int n, int i)
{
    return (i == n) ? 0 : a[i] + sum(a, n, i + 1);
}

int main(void)
{
    int a[] = {1, 2, 3, 4};
    printf("sum=%d\n", sum(a, 4, 0));
    return 0;
}
