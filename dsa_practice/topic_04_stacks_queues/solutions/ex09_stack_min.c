/* Stack with O(1) minimum using auxiliary stack. */
#include <stdio.h>

int main(void)
{
    int st[4], mn[4], top = 0, mtop = 0;
    int vals[] = {5, 2, 8};
    for (int i = 0; i < 3; i++) {
        st[top++] = vals[i];
        if (mtop == 0 || vals[i] <= mn[mtop - 1]) mn[mtop++] = vals[i];
    }
    printf("min=%d top=%d\n", mn[mtop - 1], st[top - 1]);
    return 0;
}
