/* Small deque using a circular array. */
#include <stdio.h>

#define CAP 5

int main(void)
{
    int dq[CAP] = {0};
    int front = 2, back = 2;
    dq[front = (front - 1 + CAP) % CAP] = 10;
    dq[back] = 20; back = (back + 1) % CAP;
    printf("front=%d back_item=%d\n", dq[front], dq[(back - 1 + CAP) % CAP]);
    return 0;
}
