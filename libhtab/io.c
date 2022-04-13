#include <ctype.h>
#include <stdio.h>

int read_word(char *s, int max, FILE *f){
    for (int i = 0; i < max; ++i) {
        s[i] = '\0';
    }
    char c;
    int len = 0;
    while(len < max){
        c = getc(f);
        if(c == EOF && len == 0){
            return EOF;
        }
        if(isspace(c) || c == EOF){
            return len;
        }
        s[len] = c;
        len++;
    }
    s[127] = '\0';
    while(1){
        c = getc(f);
        if(isspace(c) || c == EOF){
            return len;
        }
        len++;
    }
}