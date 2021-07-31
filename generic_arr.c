#include <string.h>
#include "generic_arr.h"

LIST_DECLARE(int)
LIST_DEFINE(int)
LIST_DECLARE(char)
LIST_DEFINE(char)

int main() {
    LIST_TYPE(int)* test = list_int_init(20);
    
    list_int_free(test);

    LIST_TYPE(char)* test2 = list_char_init(0);

    const char* words = "My name is Ben";
    for (size_t i = 0; i < strlen(words); i++) {
        list_char_pushback(test2, words[i]);
    }

    for (size_t i = 0; i < test2->sz; ++i) {
        printf("%c", *get_char(test2, i));
    }
    printf("|\n");

    printf("test2[%d] = %c\n", 5, pop_char(test2, 5));

    for (size_t i = 0; i < test2->sz; i++)
        printf("%c", *get_char(test2, i)); 
   
    printf("|\n");

    char* slice = get_char_slice(test2, 4, test2->sz - 2);

    printf("%s|\n", slice);

    free(slice);
    list_char_free(test2);
}