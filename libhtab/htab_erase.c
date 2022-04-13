#include "htab.h"
#include "htab_structs_definition.h"
#include <string.h>
#include <stdlib.h>

#define AVG_LEN_MIN 1

bool htab_erase(htab_t * t, htab_key_t key){
    htab_item* tmp;
    htab_item* tmp2;
    size_t index = htab_hash_function(key) % t->arr_size;
    tmp = t->arr_ptr[index];
    if(tmp){
        if (!strcmp(tmp->pair.key, key)) {
            if(tmp->next){
                tmp2 = t->arr_ptr[index]->next;
                free(t->arr_ptr[index]);
                t->size--;
                t->arr_ptr[index] = tmp2;
                return true;
            }
            free(t->arr_ptr[index]);
            t->size--;
            t->arr_ptr[index] = NULL;
            return true;
        }
    }

    tmp2 = t->arr_ptr[index];
    while(tmp){
        if(!strcmp(tmp->pair.key, key)){
            if(tmp->next){
                tmp2->next = tmp->next;
                free(tmp);
                t->size--;
                tmp = NULL;
                return true;
            }
            free(tmp);
            t->size--;
            tmp2->next = NULL;
            tmp = NULL;
            return true;
        }
        tmp2 = tmp;
        tmp = tmp->next;
    }

    return false;
}    // ruší zadaný záznam
