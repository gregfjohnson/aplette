/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

struct memblock {
	int *block;
	unsigned nbytes;
	struct memblock *next;
};

struct memblock *firstblock;
extern int mem_trace;
