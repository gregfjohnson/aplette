/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#ifndef MEMORY_H
#define MEMORY_H

struct memblock {
	int *block;
	unsigned nbytes;
	struct memblock *next;
};

struct memblock *firstblock;
extern int mem_trace;

void afreset();
int *alloc();
void aplfree(int *ap);

#endif
