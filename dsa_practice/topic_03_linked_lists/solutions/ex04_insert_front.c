/* Insert a node at the front. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

static void push_front(Node **head, Node *node)
{
    node->next = *head;
    *head = node;
}

int main(void)
{
    Node a = {1, NULL}, b = {2, NULL};
    Node *head = &a;
    push_front(&head, &b);
    for (Node *p = head; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
