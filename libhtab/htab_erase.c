#include "htab.h"
#include "htab_structs_definition.h"
#include <string.h>
#include <stdlib.h>

bool htab_erase(htab_t * t, htab_key_t key){
    htab_item* tmp;
    htab_item* tmp2;

    for(size_t i = 0; i < t->arr_size; ++i){
        tmp = t->arr_ptr[i];
        if(tmp){
            if (!strcmp(tmp->pair.key, key)) {
                if(tmp->next){
                    tmp2 = t->arr_ptr[i]->next;
                    free(t->arr_ptr[i]);
                    t->size--;
                    t->arr_ptr[i] = tmp2;
                    return true;
                }
                free(t->arr_ptr[i]);
                t->size--;
                t->arr_ptr[i] = NULL;
                return true;
            }
        }

        tmp2 = t->arr_ptr[i];
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
    }
    return false;
}    // ruší zadaný záznam
