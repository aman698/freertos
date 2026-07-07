/* Simple queue with shifting after dequeue. */
#include <stdio.h>

int main(void)
{
    int q[4], n = 0;
    q[n++] = 1; q[n++] = 2; q[n++] = 3;
    while (n > 0) {
        printf("%d ", q[0]);
        for (int i = 1; i < n; i++) q[i - 1] = q[i];
        n--;
    }
    putchar('\n');
    return 0;
}
