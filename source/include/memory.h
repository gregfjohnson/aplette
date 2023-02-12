/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#ifndef MEMORY_H
#define MEMORY_H

typedef struct memblock {
    int* block;
    unsigned nbytes;
    struct memblock* next;
} memblock_t;

extern memblock_t *firstblock;
extern int mem_trace;

void afreset();
void* alloc(unsigned bytes);
void aplfree(void* ap);

#endif
