#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LIST_SIZE 16

#define LIST_DECLARE(type)                                                                  \
typedef struct list_##type##_s {                                                            \
    type* data;                                                                             \
    size_t sz;                                                                              \
    size_t max_sz;                                                                          \
} list_##type;                                                                              \
list_##type* list_##type##_resize(list_##type* ls, size_t new_sz);                          \
list_##type* list_##type##_pushback(list_##type* ls, type data);                            \
list_##type* list_##type##_init(size_t sz);                                                 \
type* get_##type(list_##type* ls, long idx);                                                \
int set_##type(list_##type* ls, size_t idx, type val);                                      \

#define LIST_DEFINE(type)                                                                   \
list_##type* list_##type##_resize(list_##type* ls, size_t new_sz) {                         \
    ls = (list_##type*) realloc((void*) ls, new_sz);                                        \
    if (!ls) {                                                                              \
        fprintf(stderr, "Failed realloc in list_##type##_resize.\n");                       \
        abort();                                                                            \
    }                                                                                       \
    else {                                                                                  \
        ls->max_sz = new_sz;                                                                \
        return ls;                                                                          \
    }                                                                                       \
}                                                                                           \
list_##type* list_##type##_pushback(list_##type* ls, type val) {                            \
    if (ls->sz + 1 >= ls->max_sz)                                                           \
        ls = list_##type##_resize(ls, ls->max_sz * 2);                                      \
    ls->data[ls->sz] = val;                                                                 \
    ls->sz++;                                                                               \
    return ls;                                                                              \
}                                                                                           \
list_##type* list_##type##_init(size_t sz) {                                                \
    list_##type* ls = (list_##type*) malloc(sizeof(list_##type));                           \
    if (!ls) {                                                                              \
        fprintf(stderr, "Failed malloc in list_##type##_init.\n");                          \
        abort();                                                                            \
    }                                                                                       \
    if (sz < DEFAULT_LIST_SIZE) {                                                           \
        ls->data = (type*) calloc(DEFAULT_LIST_SIZE, sizeof(type));                         \
        ls->sz = 0;                                                                         \
        ls->max_sz = DEFAULT_LIST_SIZE;                                                     \
    } else {                                                                                \
        ls->data = (type*) calloc(sz, sizeof(type));                                        \
        ls->sz = 0;                                                                         \
        ls->max_sz = sz;                                                                    \
    }                                                                                       \
    if (!ls->data) {                                                                        \
        fprintf(stderr, "Failed malloc for ls->data in list_##type##_init.\n");             \
    }                                                                                       \
    return ls;                                                                              \
}                                                                                           \
type* get_##type(list_##type* ls, long idx) {                                               \
    if (idx >= (long) ls->max_sz) {                                                         \
        fprintf(stderr, "Attempted access to unallocated memory in get_##type.\n");         \
        abort();                                                                            \
    } else if (idx < 0) {                                                                   \
        return NULL;                                                                        \
    } else {                                                                                \
        return &(ls->data[idx]);                                                            \
    }                                                                                       \
}                                                                                           \

#define LIST_TYPE(type)                                                                     \
    list_##type                                                                             \

LIST_DECLARE(int)
LIST_DEFINE(int)

int main() {
    LIST_TYPE(int)* test = list_int_init(20);

    printf("test->sz = %uld, test->max_sz = %uld\n", test->sz, test->max_sz);
    for (size_t i = 0; i++ < test->max_sz;)
        printf("ls[%uld] = %d\n", i, *get_int(test, i));
}