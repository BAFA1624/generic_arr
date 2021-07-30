#include <stdio.h>
#include <stdlib.h>

#ifndef GENERIC_ARR_H

#define GENERIC_ARR_H

#define DEFAULT_LIST_SIZE 16
#define DEFAULT_LIST_GROWTH_FACTOR 1.5

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
void set_##type(list_##type* ls, long idx, type val);                                       \
type* pop_##type(list_##type* ls, size_t idx);                                              \
void list_##type##_free(list_##type* ls);                                                   \

#define LIST_DEFINE(type)                                                                   \
list_##type* list_##type##_resize(list_##type* ls, size_t new_sz) {                         \
    ls->data = (type*) realloc((void*) ls->data, sizeof(type) * new_sz);                          \
    if (!ls) {                                                                              \
        fprintf(stderr, "Failed realloc in list_##type##_resize.\n");                       \
        exit(-1);                                                                           \
    }                                                                                       \
    else {                                                                                  \
        ls->max_sz = new_sz;                                                                \
        return ls;                                                                          \
    }                                                                                       \
}                                                                                           \
list_##type* list_##type##_pushback(list_##type* ls, type val) {                            \
    if (ls->sz + 1 >= ls->max_sz)                                                           \
        ls = list_##type##_resize(ls, ls->max_sz * DEFAULT_LIST_GROWTH_FACTOR);             \
    ls->data[ls->sz] = val;                                                                 \
    ls->sz++;                                                                               \
    return ls;                                                                              \
}                                                                                           \
list_##type* list_##type##_init(size_t sz) {                                                \
    list_##type* ls = (list_##type*) malloc(sizeof(list_##type));                           \
    if (!ls) {                                                                              \
        fprintf(stderr, "Failed malloc in list_##type##_init.\n");                          \
        exit(-1);                                                                           \
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
        exit(-1);                                                                           \
    } else if (idx < 0) {                                                                   \
        idx *= -1;                                                                          \
        if (idx > (long) ls->sz) {                                                          \
            fprintf(stderr, "Attempted access to unallocated memory in get_##type.\n");     \
            exit(-1);                                                                       \
        } else {                                                                            \
            return &(ls->data[ls->sz - idx]);                                               \
        }                                                                                   \
    } else {                                                                                \
        return &(ls->data[idx]);                                                            \
    }                                                                                       \
}                                                                                           \
void set_##type(list_##type* ls, long idx, type val) {                                      \
    if (idx >= (long) ls->max_sz) {                                                         \
        fprintf(stderr, "Attempted access to unallocated memory in set_##type.\n");         \
        exit(-1);                                                                           \
    } else if (idx < 0) {                                                                   \
        idx *= -1;                                                                          \
        if (idx > (long) ls->max_sz) {                                                      \
            fprintf(stderr, "Attempted access to unallocated memory in set_##type.\n");     \
            exit(-1);                                                                       \
        } else {                                                                            \
            idx = ls->max_sz - idx;                                                         \
            ls->data[idx] = val;                                                            \
        }                                                                                   \
    } else {                                                                                \
        ls->data[idx] = val;                                                                \
    }                                                                                       \
                                                                                            \
    if (idx >= (long) ls->sz) {                                                             \
        ls->sz = (size_t) idx + 1;                                                          \
        printf("\tls->sz = %u\n", ls->sz);                                                  \
        list_##type##_resize(ls, ls->max_sz * DEFAULT_LIST_GROWTH_FACTOR);                  \
    }                                                                                       \
}                                                                                           \
void list_##type##_free(list_##type* ls) {                                                  \
    free(ls->data);                                                                         \
    free(ls);                                                                               \
}                                                                                           \

#define LIST_TYPE(type)                                                                     \
    list_##type                                                                             \

#endif
