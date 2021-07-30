#include <string.h>
#include "generic_arr.h"

LIST_DECLARE(int)
LIST_DEFINE(int)
LIST_DECLARE(char)
LIST_DEFINE(char)

int main() {
    LIST_TYPE(int)* test = list_int_init(20);

    printf("test->sz = %u, test->max_sz = %u\n", test->sz, test->max_sz);
    for (size_t i = 0; i < test->max_sz; i++)
        printf("ls[%u] = %d\n", i, *get_int(test, i));
    
    list_int_pushback(test, 5);
    list_int_pushback(test, 6);

    printf("test->sz = %u, test->max_sz = %u\n", test->sz, test->max_sz);
    for (size_t i = 0; i < test->max_sz; i++)
        printf("ls[%u] = %d\n", i, *get_int(test, i));

    printf("ls[-1] = %d\tls[-2] = %d\n", *get_int(test, -1), *get_int(test, -2));
    printf("test->sz = %u, test->max_sz = %u\n", test->sz, test->max_sz);
    set_int(test, 15, 1);
    printf("test->sz = %u, test->max_sz = %u\n", test->sz, test->max_sz);
    for (size_t i = 0; i < test->max_sz; i++)
        printf("ls[%u] = %d\n", i, *get_int(test, i));

    list_int_free(test);

    LIST_TYPE(char)* test2 = list_char_init(100);
    const char* words = "My name is Ben";
    for (int i = 0; i < strlen(words); i++) {
        set_char(test2, (long) i, words[i]);
    }

    for (size_t i = 0; i < test2->sz; ++i) {
        printf("%c", *get_char(test2, i));
    }
    putchar('\n');
}