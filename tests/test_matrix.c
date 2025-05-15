#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "../dependencies/headers/matrix.h"

void test_init() {
    MATRIX* m = new_matrix(2,2);
    float a = 5.6;
    void* p = &a;
    reset_matrix(m, p);

    assert(get_entry(m, 0, 0) == p);

    free_matrix(m);
    m = NULL;
    printf("PASS - test_init\n");
}

void test_array_in() {
    MATRIX* m = new_matrix(3,3);
    int a = 5, b = -1, c = -3, d = 4;
    void* V[9] = {&a, &b, &a, &b, &c, &d, &c, &a, &b};

    set_matrix(m, V, 9);

    // print_matrix(m, int_conv);

    free_matrix(m);
    printf("PASS - test_array_in\n");
}

void test_math() {
    MATRIX* m = new_matrix(2,2);
    MATRIX* t = new_matrix(2,2);
    MATRIX* b = new_matrix(2,2);
    MATRIX* s = new_matrix(3,3);
    float a = 2;
    reset_matrix(m, &a);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            float* v = get_entry(m, i, j);
            assert(*v == 2.0);
        }
    }

    multiply_matrix(m, m, t);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            float* v = get_entry(t, i, j);
            assert(*v == 8.0);
        }
    }

    add_matrix(m, m, b);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            float* v = get_entry(b, i, j);
            assert(*v == 4.0);
        }
    }

    float z = 0;
    reset_matrix(s, &z);
    copy_matrix(b, s);

    MATRIX *sm = new_matrix(3,3);
    scalar_mult(s, sm, 5);
    float *v = get_entry(sm, 0, 1);
    assert(*v == 20.);

    free_matrix(m);
    free_matrix(b);
    free_matrix(t);
    free_matrix(s);
    free_matrix(sm);
    printf("PASS - test_math\n");
}

void test_copy() {
    MATRIX* A = new_matrix(3,3);
    MATRIX* B = new_matrix(3,3);
    MATRIX* C = new_matrix(5,5);

    int a = 1, b = 2, c = -2, d = 3, z = 0;
    void* V[9] = {&a, &b, &z, &z, &d, &c, &a, &a, &c};
    
    set_matrix(A, V, 9);
    reset_matrix(B, &z);
    reset_matrix(C, &z);
    
    transpose(A, B);
    copy_matrix(A, C);

    printf("PASS - test_copy\n");
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

int main() {
    test_init();
    test_math();
    test_array_in();
    test_copy();

    return 0;
}