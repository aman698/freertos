/* Count leaf nodes. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static int leaves(Node *n)
{
    if (n == NULL) return 0;
    if (n->l == NULL && n->r == NULL) return 1;
    return leaves(n->l) + leaves(n->r);
}

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    printf("leaves=%d\n", leaves(&a));
    return 0;
}
