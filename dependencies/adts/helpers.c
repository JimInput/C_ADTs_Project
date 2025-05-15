#include "../headers/helpers.h"
#define N 20


int min(int x, int y) {
    return (x < y) ? x : y;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

void int_conv(void* v, char* out, size_t size) {
    snprintf(out, size, "%d", *(int*)v);
}

void float_conv(void* v, char* out, size_t size) {
    snprintf(out, size, "%.3f", *(float*)v);
}

void char_conv(void* v, char* out, size_t size) {
    snprintf(out, size, "%c", *(char*)v);
}
