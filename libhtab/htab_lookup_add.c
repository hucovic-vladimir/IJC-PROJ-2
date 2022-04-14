/**
 * @file htab_lookup_add.c
 * @name IJC - Domácí úkol 2, příklad b), 14.4.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 11.2.0
 */

#include "htab.h"
#include "htab_structs_definition.h"
#include <string.h>
#include <stdlib.h>

#define AVG_LEN_MAX 0.75

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key){
    if(!t){
        return NULL;
    }

    htab_item* tmp;
    tmp = t->arr_ptr[htab_hash_function(key) % t->arr_size];
    while(tmp){
        if(!strcmp(tmp->pair.key, key)){
            return &(tmp->pair);
        }
        tmp = tmp->next;
    }

    double avgBucketLen = t->size / t->arr_size;
    if(avgBucketLen > AVG_LEN_MAX){
        htab_resize(t, t->arr_size*2);
    }

    char* keyCopy = calloc(strlen(key)+1, sizeof(char));
    htab_item* newItem = calloc(1, sizeof(htab_item));
    if(!newItem){
        return NULL;
    }
    strcpy(keyCopy, key);
    newItem->next = NULL;
    newItem->pair.key = keyCopy;
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
