#include "htab.h"
#include "htab_structs_definition.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key) {
    if (!t) {
        return NULL;
    }
    htab_item *tmp;
    for (unsigned long i = 0; i < t->arr_size; ++i) {
        tmp = t->arr_ptr[i];
        while (tmp) {
            if (!strcmp(tmp->pair.key, key)) {
                return &(tmp->pair);
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}  // hledání

