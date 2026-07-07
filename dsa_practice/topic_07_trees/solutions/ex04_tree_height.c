/* Compute tree height. Empty tree height is 0. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static int height(Node *n)
{
    if (n == NULL) return 0;
    int lh = height(n->l), rh = height(n->r);
    return 1 + (lh > rh ? lh : rh);
}

int main(void)
{
    Node c = {3, NULL, NULL}, b = {2, &c, NULL}, a = {1, &b, NULL};
    printf("height=%d\n", height(&a));
    return 0;
}
