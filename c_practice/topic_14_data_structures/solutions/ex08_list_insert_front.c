/*
 * ex08_list_insert_front.c - Insert nodes at the front of a list.
 * Key concept: new node points to old head, then head changes.
 */
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node_t;

static void push_front(Node_t **head, Node_t *node)
{
    node->next = *head;
    *head = node;
}

int main(void)
{
    Node_t a = {1, NULL};
    Node_t b = {2, NULL};
    Node_t *head = NULL;
    push_front(&head, &a);
    push_front(&head, &b);

    for (Node_t *cur = head; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }
    return 0;
}
