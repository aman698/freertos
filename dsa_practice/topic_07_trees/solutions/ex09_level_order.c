/* Level order traversal using a queue. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    Node *q[4] = {&a};
    int head = 0, tail = 1;
    while (head < tail) {
        Node *n = q[head++];
        printf("%d ", n->v);
        if (n->l) q[tail++] = n->l;
        if (n->r) q[tail++] = n->r;
    }
    putchar('\n');
    return 0;
}
