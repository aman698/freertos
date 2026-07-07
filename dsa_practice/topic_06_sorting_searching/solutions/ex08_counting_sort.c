/* Counting sort for small non-negative range. */
#include <stdio.h>

int main(void)
{
    int a[] = {3, 1, 2, 1, 0};
    int count[4] = {0};
    for (int i = 0; i < 5; i++) count[a[i]]++;
    for (int v = 0; v < 4; v++) while (count[v]-- > 0) printf("%d ", v);
    putchar('\n');
    return 0;
}
