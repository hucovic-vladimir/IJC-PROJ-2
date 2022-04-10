#ifndef LIBHTAB_HTAB_STRUCTS_DEFINITION_H
#define LIBHTAB_HTAB_STRUCTS_DEFINITION_H
#include "htab.h"

typedef struct htab_item{
    struct htab_item* next;
    htab_pair_t pair;
} htab_item;

typedef struct htab{
        unsigned long size;
        unsigned long arr_size;
        htab_item** arr_ptr;
} htab_t;

#endif //LIBHTAB_HTAB_STRUCTS_DEFINITION_H
