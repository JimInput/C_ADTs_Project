#include "../headers/queue.h"
#include "../headers/node.h"
#include "../headers/helpers.h"

QUEUE* init_queue() {
    QUEUE* q = malloc(sizeof(QUEUE));
    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->len = 0;

    return q;
}

void free_queue(QUEUE* q) {
    if (q->len > 0) {
        free_list(q->head);
    }

    free(q);
}

void put(QUEUE* q, void* d) {
    if (q == NULL)
        return;
    add_last(&q->head, &q->tail, d);
    q->len++;
}

void* get(QUEUE* q) {
    if (q == NULL)
        return NULL;

    if (q->len == 0) {
        return NULL;
    }
    NODE* item = remove_first(&q->head, &q->tail);
    void* d = item->data;
    free_node(item);
    q->len--;
    return d;
}

void print_queue(QUEUE* q, void (*f)(void*, char*, size_t)) {
    int og_len = q->len;
    for (int i = 0; i < og_len; i++) {
        char out[TEST_BUFFER_SIZE];
        f(get(q), out, TEST_BUFFER_SIZE);
        printf("%3s ", out);
    }
    printf("\n");
}