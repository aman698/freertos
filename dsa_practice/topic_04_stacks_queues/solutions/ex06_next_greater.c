/* Next greater element using monotonic stack of indices. */
#include <stdio.h>

int main(void)
{
    int a[] = {2, 1, 4, 3};
    int ans[] = {-1, -1, -1, -1};
    int st[4], top = 0;
    for (int i = 0; i < 4; i++) {
        while (top > 0 && a[i] > a[st[top - 1]]) ans[st[--top]] = a[i];
        st[top++] = i;
    }
    for (int i = 0; i < 4; i++) printf("%d ", ans[i]);
    putchar('\n');
    return 0;
}
