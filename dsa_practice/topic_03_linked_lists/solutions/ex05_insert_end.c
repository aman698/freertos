/* Insert a node at the end. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

static void push_back(Node **head, Node *node)
{
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return;
    }
    Node *p = *head;
    while (p->next != NULL) p = p->next;
    p->next = node;
}

int main(void)
{
    Node a = {1, NULL}, b = {2, NULL};
    Node *head = &a;
    push_back(&head, &b);
    for (Node *p = head; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
