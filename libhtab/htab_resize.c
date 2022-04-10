#include "htab.h"
#include "htab_structs_definition.h"
#include <stdlib.h>

void htab_resize(htab_t* t, size_t newn){
    if(!t) {
        return;
    }

    htab_t* newTab = htab_init(newn);
    if(!newTab){
        return;
    }

    htab_pair_t* newPair;
    htab_item* tmp;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp = t->arr_ptr[i];
        while(tmp){
            newPair = htab_lookup_add(newTab, tmp->pair.key);
            if(!newPair){
                return;
            }
            newPair->value = tmp->pair.value;
            tmp = tmp->next;
        }
    }
    htab_clear(t);
    free(t->arr_ptr);
    t->arr_size = newTab->arr_size;
    t->size = newTab->size;
    t->arr_ptr = newTab->arr_ptr;
    free(newTab);
}
