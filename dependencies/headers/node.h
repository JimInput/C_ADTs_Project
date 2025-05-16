#ifndef __NODE__H__
#define __NODE__H__

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    void* data;
} NODE;

NODE* new_node(void* d);

void free_node(NODE* head);

void free_list(NODE* head);

void add_last(NODE** head, NODE** tail, void* d);

NODE* remove_first(NODE** head, NODE** tail);

#endif