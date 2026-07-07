/*
 * ex09_list_remove_value.c - Remove a node by value.
 * Key concept: pointer-to-pointer simplifies head removal.
 */
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node_t;

static bool remove_value(Node_t **head, int value)
{
    while (*head != NULL) {
        if ((*head)->value == value) {
            *head = (*head)->next;
            return true;
        }
        head = &(*head)->next;
    }
    return false;
}

int main(void)
{
    Node_t c = {3, NULL};
    Node_t b = {2, &c};
    Node_t a = {1, &b};
    Node_t *head = &a;
    remove_value(&head, 2);

    for (Node_t *cur = head; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }
    return 0;
}
