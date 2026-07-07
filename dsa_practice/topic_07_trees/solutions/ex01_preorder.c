/* Binary tree preorder traversal. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static void preorder(Node *n)
{
    if (n == NULL) return;
    printf("%d ", n->v);
    preorder(n->l);
    preorder(n->r);
}

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    preorder(&a); putchar('\n');
    return 0;
}
