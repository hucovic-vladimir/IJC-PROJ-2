#include "htab.h"
#include "htab_structs_definition.h"
#include <stdlib.h>

htab_t *htab_init(size_t n){
    htab_t* ht = calloc(1, sizeof(htab_t));
    if(!ht){
        return NULL;
    }
    ht->arr_size = n;
    ht->size = 0;
    ht->arr_ptr = calloc(n, sizeof(htab_item*));
    if(!ht->arr_ptr){
        return NULL;
    }
    return ht;
}
