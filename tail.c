/**
 * @file tail.c
 * @name IJC - Domácí úkol 2, příklad a), 14.4.2022
 * @author Vladimír Hucovič, FIT
 * Přeloženo pomocí GCC verze 11.2.0
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 4096

typedef struct circularBufferItem{
    struct circularBufferItem* next;
    char* line;
} circularBufferItem;

typedef struct{
    unsigned long maxSize;
    unsigned long currSize;
    circularBufferItem *head;
    circularBufferItem *tail;
} circularBuffer;


int circularBufferInit(circularBuffer *buf, unsigned long maxSize){
    if(buf){
        buf->maxSize = maxSize;
        buf->currSize = 0;
        buf->head = NULL;
        buf->tail = NULL;
    }
    return 1;
}

int circularBufferAdd(circularBuffer *buf, circularBufferItem* item){
    if(!buf){
        exit(1);
    }

    if(buf->currSize == 1 && buf->maxSize == 1){
        free(buf->head->line);
        free(buf->head);
        buf->currSize = 0;
        buf->head = NULL;
    }

    if(buf->head == NULL) {
        buf->head = item;
        buf->tail = item;
        buf->tail->next = buf->head;
        buf->currSize++;
        return 1;
    }
    if(buf->currSize != buf->maxSize){
        buf->tail->next = item;
        buf->tail = item;
        buf->tail->next = buf->head;
        buf->currSize++;
    }
    else{
        circularBufferItem* tmp = buf->head;
        buf->head = buf->head->next;
        free(tmp->line);
        free(tmp);
        buf->tail->next = item;
        buf->tail = item;
        buf->tail->next = buf->head;
    }
    return 2;
}

void circularBufferPrint(circularBuffer *buf){
    struct circularBufferItem* temp = buf->head;
    for(unsigned int i = 0; i < buf->currSize; i++){
        printf("%s", temp->line);
        temp = temp->next;
    }
}

void circularBufferFree(circularBuffer* buf){
    circularBufferItem* tmp = buf->head;
    while(tmp != buf->tail){
        buf->head = buf->head->next;
        free(tmp->line);
        free(tmp);
        tmp = buf->head;
    }
    if(buf->head){
        free(buf->head->line);
        free(buf->head);
    }
    free(buf);
}

void handleMemoryErrors(){
    fprintf(stderr, "Error: failed to allocate memory. Exiting.\n");
    exit(1);
}


circularBufferItem* itemInit(){
    circularBufferItem* item = calloc(1, sizeof(circularBufferItem));
    if(!item){
        handleMemoryErrors();
    }
    item->line = calloc(MAX_LINE_LENGTH, sizeof(char));
    if(!item->line){
        handleMemoryErrors();
    }
    item->next = NULL;
    return item;
}

int main(int argc, char* argv[]){
    FILE *f = stdin;
    int argument = 10;
    char* endptr = "";

    if(argc > 1){
        if(argv[1][0] == '-'){
            if(argv[1][1] != 'n'){
                fprintf(stderr, "Neznamy prepinac: -%c\n", argv[1][1]);
                exit(1);
            }
            if(argv[1][2] != '\0'){
                fprintf(stderr, "Chyba! Pouziti: ./tail [-n NUMBER] [FILE]\n");
                exit(1);
            }
            if(argc < 3){
                fprintf(stderr, "Chyba! Po prepinaci -n musi nasledovat kladne cislo.\n");
                exit(1);
            }
            argument = strtol(argv[2], &endptr, 10);
            if(argument == 0){
                if(strcmp(endptr, "")){
                    fprintf(stderr, "Spatna hodnota po prepinaci -n! Musi to byt kladne cislo.\n");
                }
                exit(1);
            }
            if(strcmp(endptr, "")){
                fprintf(stderr, "Spatna hodnota po prepinaci -n! Musi to byt kladne cislo.\n");
                exit(1);
            }
            if(argc > 3){
                char* filename = argv[3];
                f = fopen(filename, "r");
                if(f == NULL){
                    fprintf(stderr,"Soubor %s neexistuje!\n", argv[3]);
                    exit(1);
                }
            }
        }
        else{
            char* filename = argv[1];
            f = fopen(filename, "r");
            if(f == NULL){
                fprintf(stderr,"Soubor %s neexistuje!\n", argv[1]);
                exit(1);
            }
        }
    }

    circularBuffer* tail = calloc(1, sizeof(circularBuffer));
    if(!tail){
        handleMemoryErrors();
    }
    circularBufferInit(tail, argument);

    circularBufferItem* item;
    int lineTooLong = 0;
    for(;;){
        item = itemInit();
        if(fgets(item->line, MAX_LINE_LENGTH, f) == NULL){
            free(item->line);
            free(item);
            break;
        }
        else{
            if(item->line[4094] != '\0' && item->line[4094] != '\n'){
                item->line[4094] = '\n';
                if(!lineTooLong){
                    fprintf(stderr, "Varovani: Nektere radky jsou prilis dlouhe, budou useknuty\n");
                    lineTooLong = 1;
                }
                char cutaway;
                while((cutaway = getc(f))){
                    if(cutaway == '\n'){
                        break;
                    }
                }

            }
            circularBufferAdd(tail, item);
        }
    }

    if(tail){
        circularBufferPrint(tail);
        circularBufferFree(tail);
    }
}