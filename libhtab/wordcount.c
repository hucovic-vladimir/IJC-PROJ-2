/**
 * @file wordcount.c
 * @name IJC - Domácí úkol 2, příklad b), 14.4.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 11.2.0
 */


#include "htab.h"
#include "htab_structs_definition.h"
#include <stdio.h>

#define MAX_WORD_LEN 127


#ifdef HASHTEST
size_t htab_hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
#endif

extern int read_word(char *s, int max, FILE *f);

void printPairContent(htab_pair_t *p){
    printf("%s\t%d\n", p->key, p->value);
}

int main(){
    htab_t *t = htab_init(97);
    int len;
    char s[128] = {0};

    htab_pair_t* pair;
    int wordTooLong = 0;
    while((len = read_word(s, MAX_WORD_LEN+1, stdin)) != EOF){
        if(len > 0){
            if(len > MAX_WORD_LEN && wordTooLong == 0){
                fprintf(stderr, "Nektera slova jsou prilis dlouha! Slova delsi nez %d budou zkracena!\n", MAX_WORD_LEN);
                wordTooLong++;
            }
            pair = htab_lookup_add(t, s);
            pair->value++;
        }
    }

    htab_for_each(t, printPairContent);
    htab_free(t);
}