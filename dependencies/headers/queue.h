// class for implementing the queue ADT using the nary nodes in this project

#ifndef __QUEUE__H__
#define __QUEUE__H__

#include <stdio.h>
#include <stddef.h>
#include "node.h"

typedef struct Queue {
    NODE* head;
    NODE* tail;
    int len;
} QUEUE;

// initializes a new empty queue.
QUEUE* init_queue();

// frees the data allocated to a queue.
void free_queue(QUEUE* q);

// puts data on the queue.
void put(QUEUE* q, void* d);

// gets data from the queue using LIFO.
void* get(QUEUE* q);

void print_queue(QUEUE* q, void (*f)(void*, char*, size_t));

#endif