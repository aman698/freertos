/* Frequency count for small non-negative integers. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 1, 3, 2, 1};
    int freq[4] = {0};
    for (int i = 0; i < 6; i++) freq[a[i]]++;
    for (int v = 0; v < 4; v++) printf("%d:%d\n", v, freq[v]);
    return 0;
}
