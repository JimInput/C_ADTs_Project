#include "../headers/node.h"
#include "../headers/helpers.h"
#include <stddef.h>

NODE* new_node(void* d) {
    NODE* n = malloc(sizeof(NODE));
    if (n == NULL) {
        return NULL;
    }

    n->next = NULL;
    n->prev = NULL;
    n->data = d;

    return n;
}

void free_node(NODE* head) {
    if (head == NULL)
        return;
    free(head);
}

void free_list(NODE* head) {
    if (head == NULL)
        return;

    while (head != NULL) {
        NODE* temp = head;
        head = head->next;
        free(temp);
    }
}

void add_last(NODE** head, NODE** tail, void* d) {
    if (tail == NULL) 
        return;

    NODE* n = new_node(d);

    if (*tail == NULL) {
        (*tail) = n;
        (*head) = n;
        return;
    }

    
    (*tail)->next = n;
    n->prev = *tail;
    (*tail) = n;
}

NODE* remove_first(NODE** head, NODE** tail) {
    if (head == NULL || *head == NULL)
        return NULL;

    NODE* old_head = *head;
    (*head) = old_head->next;
    if (*head != NULL)
        (*head)->prev = NULL;
    else
        *tail = NULL;

    old_head->next = NULL;

    return old_head;
}