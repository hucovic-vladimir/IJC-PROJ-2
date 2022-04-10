#include "htab.h"
#include "htab_structs_definition.h"

size_t htab_size(const htab_t* t){
    return t->arr_size;
}
