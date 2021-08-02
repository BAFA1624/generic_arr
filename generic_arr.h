

#ifndef GENERIC_ARR_H_

#include <stdio.h>
#include <stdlib.h>

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
	type pop_##type(list_##type* ls, size_t idx);                                               \
	void list_##type##_free(list_##type* ls);                                                   \
	list_##type* get_##type##_slice(list_##type* ls, size_t start_idx, size_t end_idx);                \
	size_t validate_##type##_idx(list_##type* ls, size_t idx);                                  \
	void clear_##type##_bits(list_##type* ls, size_t start_idx, size_t end_idx);                \
	long binary_##type##_search(list_##type* ls, type search_val, int (*compare_func)(const void* a, const void* b)); \

#define LIST_DEFINE(type)                                                                   \
	list_##type* list_##type##_resize(list_##type* ls, size_t new_sz) {                         \
		ls->data = (type*) realloc((void*) ls->data, sizeof(type) * new_sz);                    \
		if (!ls) {                                                                              \
			fprintf(stderr, "Failed realloc in list_##type##_resize.\n");                       \
			exit(-1);                                                                           \
		} else {                                  \
			if (new_sz > ls->max_sz)                                                            \
			clear_##type##_bits(ls, ls->max_sz, new_sz);                                    \
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
			ls->data = (type*) malloc(DEFAULT_LIST_SIZE * sizeof(type));                        \
			ls->sz = 0;                                                                         \
			ls->max_sz = DEFAULT_LIST_SIZE;                                                     \
		} else {                                                                                \
			ls->data = (type*) malloc(sz * sizeof(type));                                       \
			ls->sz = 0;                                                                         \
			ls->max_sz = sz;                                                                    \
		}                                                                                       \
		if (!ls->data) {                                                                        \
			fprintf(stderr, "Failed malloc for ls->data in list_##type##_init.\n");             \
		}                                                                                       \
		clear_##type##_bits(ls, 0, ls->max_sz);                                                 \
		return ls;                                                                              \
	}                                                                                           \
	type* get_##type(list_##type* ls, long idx) {                                               \
		if (idx >= (long) ls->sz) {                                                             \
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
		if ((size_t) idx >= ls->sz) {                                                           \
			ls->sz = (size_t) idx + 1;                                                          \
			if (ls->sz >= ls->max_sz) {                                                         \
				list_##type##_resize(ls, ls->max_sz * DEFAULT_LIST_GROWTH_FACTOR);              \
			}                                                                                   \
		}                                                                                       \
	}                                                                                           \
	type pop_##type(list_##type* ls, size_t idx) {                                              \
		type return_val = ls->data[idx];                                                        \
		for (size_t i = idx; i < ls->sz; ++i) {                                                 \
			ls->data[i] = ls->data[i+1];                                                        \
		}                                                                                       \
		ls->sz--;                                                                               \
		return return_val;                                                                      \
	}                                                                                           \
	void list_##type##_free(list_##type* ls) {                                                  \
		free(ls->data);                                                                         \
		free(ls);                                                                               \
	}                                                                                           \
	list_##type* get_##type##_slice(list_##type* ls, size_t start_idx, size_t end_idx) {               \
		list_##type* result = list_##type##_init(end_idx - start_idx);                      \
		for (size_t i = start_idx; i < end_idx; ++i)                                            \
		list_##type##_pushback(result, ls->data[i]); \
		return result;                                                                          \
	}                                                                                           \
	void clear_##type##_bits(list_##type* ls, size_t start_idx, size_t end_idx) {               \
		for (size_t i = start_idx; i < end_idx; ++i)                                            \
		ls->data[i] = (ls->data[i] & 0);                                                    \
	}                                                                                           \
	long binary_##type##_search(list_##type* ls, type search_val, int (*compare_func)(const void* a, const void* b)) {\
		long idx, compare_result, left_ptr = 0, right_ptr = ls->sz;\
		while (left_ptr != right_ptr) {\
			idx = (left_ptr + right_ptr) / 2;\
			printf("\tidx = %ld, left_ptr = %ld, right_ptr = %ld\n", idx, left_ptr, right_ptr);\
			compare_result = (size_t) compare_func((const void*) &search_val, (const void*) &ls->data[idx]);\
			printf("\tcomparing: search_val = %ld, ls->data[%ld] = %ld, compare_result = %ld\n\n", search_val, idx, ls->data[idx], compare_result);\
			if (compare_result == 0) {\
				printf("\tResult: idx = %ld, left_ptr = %ld, right_ptr = %ld\n", idx, left_ptr, right_ptr);\
				return idx;\
			} else if (compare_result > 0) {\
				left_ptr = idx;\
			} else if (compare_result < 0) {\
				right_ptr = idx;\
			}\
			if (left_ptr > right_ptr) {\
				fprintf(stderr, "binary search went wrong, left_ptr > right_ptr.\n");\
				exit(-1);\
			}\
		}\
		return -1;\
	}\


/*size_t validate_idx(list_##type* ls, size_t idx) {

  }*/

#define LIST_TYPE(type)                                                                     \
	list_##type                                                                             \

#endif  //  GENERIC_ARR_H_
