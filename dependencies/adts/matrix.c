#include "../headers/helpers.h"
#include "../headers/matrix.h"

MATRIX* new_matrix(int nrows, int ncols) {
    // allocate space for matrix struct
    MATRIX* newM = (MATRIX*) malloc(sizeof(MATRIX));

    // allocate space for the pointers to arrays
    void*** data = malloc(nrows*sizeof(void**));
    int** ownership = malloc(nrows*sizeof(int*));

    // allocate space for all elements
    void** storage = malloc(nrows*ncols*sizeof(void*));
    int* owner_storage = calloc(nrows*ncols, sizeof(int));

    if (newM == NULL || data == NULL || storage == NULL || ownership == NULL || owner_storage == NULL) {
        free(newM);
        free(data);
        free(ownership);
        free(storage);
        free(owner_storage);
        return NULL;
    }

    for (int i = 0; i < nrows; i++) {
        data[i] = storage + ncols*i;
        ownership[i] = owner_storage + ncols*i;
    }
    newM->data = data;
    newM->nrows = nrows;
    newM->ncols = ncols;
    newM->ownership = ownership;

    reset_matrix(newM, NULL);

    return newM;
}

void free_matrix(MATRIX* m) {
    if (m == NULL) {
        return;
    }
    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            if (m->ownership[i][j]) {
                free(m->data[i][j]);
            }
        }
    }
    if (m->data) {
        free(m->data[0]);
        free(m->data);
    }

    if (m->ownership) {
        free(m->ownership[0]);
        free(m->ownership);
    }

    free(m);
}

// prints matrix if matrix has values which make sense
void print_matrix(MATRIX* m, void (*f)(void*, char*, size_t)) {
    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            char out[20];
            f(m->data[i][j], out, MATRIX_BUFFER_SIZE);
            printf("%3s ", out);
        }
        printf("\n");
    }
}

void put_entry(MATRIX* m, int row, int col, void* v) {
    if (m == NULL || m->data == NULL || row >= m->nrows || col >= m->ncols) {
        return;
    }
    m->ownership[row][col] = FALSE;
    m->data[row][col] = v;
}

void* get_entry(MATRIX* m, int row, int col) {
    if (m == NULL || m->data == NULL || row >= m->nrows || col >= m->ncols) {
        return NULL;
    }

    return m->data[row][col];
}

void reset_matrix(MATRIX* m, void* v) {
    if (m == NULL || m->data == NULL) {
        return;
    }

    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            m->data[i][j] = v;
            m->ownership[i][j] = FALSE;
        }
    }
}

void set_matrix(MATRIX* m, void** V, int n) {
    if (m == NULL || m->data == NULL || V == NULL || n > m->nrows * m->ncols)
        return;

    for (int i = 0; i < n; i++) {
        int row = i / m->ncols;
        int col = i % m->ncols;
        m->data[row][col] = V[i];
        m->ownership[row][col] = FALSE;
    }
}

int compare_matrix(MATRIX *m, MATRIX *n) {
    if (m == NULL || m->data == NULL || n == NULL || n->data == NULL) {
        return MATRIX_NOT_DEFINED;
    }

    if (m->nrows != n->nrows || m->ncols != n->ncols) {
        return MATRIX_DIMENSIONS_INCORRECT;
    }

    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            if (m->data[i][j] != n->data[i][j])
                return FALSE;
        }
    }

    return TRUE;
}

void copy_matrix(MATRIX *m, MATRIX *t) {
    if (m == NULL || t == NULL || m->data == NULL || t->data == NULL) {
        return;
    }

    for (int i = 0; i < min(m->nrows, t->nrows); i++) {
        for (int j = 0; j < min(m->ncols, t->ncols); j++) {
            t->data[i][j] = m->data[i][j];
            t->ownership[i][j] = FALSE;
        }
    }
}

void transpose(MATRIX *m, MATRIX *t) {
    if (m == NULL || t == NULL || m->data == NULL || t->data == NULL || m->nrows != t->ncols || m->ncols != t->nrows)
        return;
    
    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            t->data[j][i] = m->data[i][j];
            t->ownership[j][i] = FALSE;
        }
    }
}

void add_matrix(MATRIX* m, MATRIX* n, MATRIX* t) {
    if (m == NULL || m->data == NULL || n == NULL || n->data == NULL || t == NULL || t->data == NULL || m->nrows != n->nrows || m->nrows != t->nrows || n->nrows != t->nrows || m->ncols != n->ncols || m->ncols != t->ncols || n->ncols != t->ncols)
        return;
    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            float *a = malloc(sizeof(float));
            *a = *(float*)m->data[i][j] + *(float*)n->data[i][j];
            t->data[i][j] = a;
            t->ownership[i][j] = TRUE;
        }
    }
}

void multiply_matrix(MATRIX* m, MATRIX* n, MATRIX* t) {
    if (m == NULL || m->data == NULL || n == NULL || n->data == NULL || t == NULL || t->data == NULL || m->ncols != n->nrows || m->nrows != t->nrows || n->ncols != t->ncols)
        return;

    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < n->ncols; j++) {
            float sum = 0;
            for (int p = 0; p < m->ncols; p++) {
                sum += *(float*)m->data[i][p] * *(float*)n->data[p][j];
            }
            float *a = malloc(sizeof(float));
            *a = sum;
            t->data[i][j] = a;
            t->ownership[i][j] = TRUE;
        }
    }
}

void scalar_mult(MATRIX *m, MATRIX *t, float c) {
    if (m == NULL || t == NULL || m->data == NULL || t->data == NULL || m->nrows != t->nrows || m->ncols != t->ncols) {
        return;
    }

    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            float *b = malloc(sizeof(float));
            *b = c * *(float*) m->data[i][j];
            t->data[i][j] = b;
            t->ownership[i][j] = TRUE;
        }
    }
}
