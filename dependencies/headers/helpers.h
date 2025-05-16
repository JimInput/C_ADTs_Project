#ifndef __HELPERS__H__
#define __HELPERS__H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define MATRIX_NOT_DEFINED -1
#define LL_EMPTY -1
#define QUEUE_EMPTY -1
#define MATRIX_DIMENSIONS_INCORRECT -2
#define TEST_BUFFER_SIZE 20
#define MAX_CHILDREN 16



// returns value of smaller number
int min(int x, int y);

// returns value of the greater number
int max(int x, int y);

// gets the int value of a function if void* points to an int.
void int_conv(void* v, char* out, size_t size);

// gets the float value of a void* if void* points to a float.
void float_conv(void* v, char* out, size_t size);

// gets the char value of a void* if void* points to a char.
void char_conv(void* v, char* out, size_t size);

#endif