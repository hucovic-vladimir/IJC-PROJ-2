#include "htab.h"
#include "htab_structs_definition.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LEN 127

extern int read_word(char *s, int max, FILE *f);

void printPairContent(htab_pair_t *p){
    printf("%s\t%d\n", p->key, p->value);
}

int main(){
    htab_t *t = htab_init(13);
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