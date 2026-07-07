/* Binary tree inorder traversal. */
#include <stdio.h>

typedef struct Node { int v; struct Node *l, *r; } Node;

static void inorder(Node *n)
{
    if (n == NULL) return;
    inorder(n->l);
    printf("%d ", n->v);
    inorder(n->r);
}

int main(void)
{
    Node b = {2, NULL, NULL}, c = {3, NULL, NULL}, a = {1, &b, &c};
    inorder(&a); putchar('\n');
    return 0;
}
