/* Reverse a singly linked list. */
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

static Node *reverse(Node *head)
{
    Node *prev = NULL;
    while (head != NULL) {
        Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

int main(void)
{
    Node c = {3, NULL}, b = {2, &c}, a = {1, &b};
    Node *head = reverse(&a);
    for (Node *p = head; p != NULL; p = p->next) printf("%d ", p->data);
    putchar('\n');
    return 0;
}
