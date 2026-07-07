/* Binary tree postorder traversal. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static void postorder(Node *n)
{
    if (n == NULL) return;
    postorder(n->l);
    postorder(n->r);
    printf("%d ", n->v);
}

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    postorder(&a); putchar('\n');
    return 0;
}
