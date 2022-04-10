#include "htab.h"
#include "htab_structs_definition.h"
#include <string.h>
#include <stdlib.h>

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key){
    if(!t){
        return NULL;
    }

    htab_item* tmp;
    for(unsigned long i = 0; i < t->arr_size; ++i){
        tmp = t->arr_ptr[i];
        while(tmp){
            if(!strcmp(tmp->pair.key, key)){
                return &(tmp->pair);
            }
            tmp = tmp->next;
        }
    }
    htab_item* newItem = calloc(1, sizeof(htab_item));
    if(!newItem){
        return NULL;
    }
    newItem->next = NULL;
    newItem->pair.key = key;
    newItem->pair.value = 0;

    size_t index = htab_hash_function(key) % t->arr_size;
    tmp = t->arr_ptr[index];
    if(!tmp){
        t->arr_ptr[index] = newItem;
        t->size++;
        return &(newItem->pair);
    }
    while(tmp) {
        if(!tmp->next){
            tmp->next = newItem;
            t->size++;
            return &(newItem->pair);
        }
        tmp = tmp->next;
    }
    return NULL;
}
