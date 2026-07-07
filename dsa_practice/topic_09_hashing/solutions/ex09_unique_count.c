/* Count unique values using a small set table. */
#include <stdio.h>

int main(void)
{
    int a[] = {1, 2, 2, 3, 1};
    int seen[10] = {0}, unique = 0;
    for (int i = 0; i < 5; i++) {
        if (!seen[a[i]]) {
            seen[a[i]] = 1;
            unique++;
        }
    }
    printf("unique=%d\n", unique);
    return 0;
}
