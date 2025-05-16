#ifndef __MATRIX__H__
#define __MATRIX__H__

// typedef Matrix
typedef struct Matrix {
    int nrows;
    int ncols;
    void*** data;
    int** ownership;
} MATRIX;

// Allocates memory to create a new matrix
MATRIX* new_matrix(int nrows, int ncols);

// Deallocates memory of a matrix
void free_matrix(MATRIX* m);

// Sets all entries in a matrix to value v
void reset_matrix(MATRIX* m, void* v);

void set_matrix(MATRIX* m, void** V, int n);

// Compares all entries in matrix m to matrix n, returns 1 if true, 0 if false. -1 if something is NULL, -2 if different dimensions.
int compare_matrix(MATRIX* m, MATRIX* n);

// Updates the value in entry [row,col] with value v
void put_entry(MATRIX* m, int row, int col, void* v);

// Gets the value at entry [row,col].
void* get_entry(MATRIX* m, int row, int col);

// Writes the values from matrix m into as much available space as possible in matrix t. For example if m is of size mxn, and
// the output is of size axb where m<a and n<b the rows 0,...,a adn column 0,...,b are written into t.
void copy_matrix(MATRIX* m, MATRIX* t);

// Write the transpose of matrix m into t.
void transpose(MATRIX* m, MATRIX* t);

// print matrix
void print_matrix(MATRIX* m, void (*f)(void*, char*, size_t));

// Adds two matrices m and n and writes result into t, matrices must be the same size
void add_matrix(MATRIX* m, MATRIX* n, MATRIX* t);

// Multiplies two matrices m and n and writes result into t, cols in m must equal rows in n, and t must be of correct size.
void multiply_matrix(MATRIX* m, MATRIX* n, MATRIX* t);

// Performs scalar multiplication with a float c
void scalar_mult(MATRIX *m, MATRIX *t, float c);

#endif
