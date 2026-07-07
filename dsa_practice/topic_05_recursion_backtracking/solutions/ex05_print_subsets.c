/* Print all subsets with include/exclude recursion. */
#include <stdio.h>

static void subsets(const int a[], int n, int i, int chosen[], int k)
{
    if (i == n) {
        printf("{");
        for (int j = 0; j < k; j++) printf("%d", chosen[j]);
        puts("}");
        return;
    }
    subsets(a, n, i + 1, chosen, k);
    chosen[k] = a[i];
    subsets(a, n, i + 1, chosen, k + 1);
}

int main(void)
{
    int a[] = {1, 2, 3}, chosen[3];
    subsets(a, 3, 0, chosen, 0);
    return 0;
}
