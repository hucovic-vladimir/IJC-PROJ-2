//
// Created by vladimir on 4/9/22.
//

#ifndef PROJ2_TAIL_H
#define PROJ2_TAIL_H

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


#endif //PROJ2_TAIL_H
