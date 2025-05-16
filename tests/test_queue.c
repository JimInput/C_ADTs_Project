#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../dependencies/headers/queue.h"
#include "../dependencies/headers/helpers.h"

void test_init() {
    int a = 2, b = 5, c = -2, d = 3;
    QUEUE* q = init_queue();
    put(q, &a);
    put(q, &b);
    put(q, &c);
    put(q, &d);

    assert(q->len == 4);

    print_queue(q, int_conv);

    printf("PASS - test_init\n");
}

int main() {
    test_init();

    return 0;
}