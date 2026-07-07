/* Count all nodes in a binary tree. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static int count(Node *n) { return n == NULL ? 0 : 1 + count(n->l) + count(n->r); }

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    printf("nodes=%d\n", count(&a));
    return 0;
}
