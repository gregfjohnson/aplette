/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdlib.h>
#include <inttypes.h>
#include "apl.h"
#include "utility.h"
#include "memory.h"

void *alloc(unsigned nbytes) {
    struct memblock* newblock;

    if (nbytes <= 0)
        return 0;

    newblock = (struct memblock*)malloc(sizeof(struct memblock));

    if (newblock == 0)
        goto failed;

    if (mem_trace) {
        printf("[alloc: %ld bytes at %p (memblock)",
            sizeof(struct memblock), (void *) newblock);
    }

    newblock->nbytes = nbytes;
    newblock->block = malloc(nbytes);

    if (newblock->block == 0)
        goto failed;

    if (mem_trace) {
        printf(", %d bytes at %p (data)]\n",
            nbytes, (void *) newblock->block);
    }

    newblock->next = firstblock;
    firstblock = newblock;

    return newblock->block;

failed:
    printf("Unable to obtain requested memory\n");
    printf("%d bytes were requested\n", nbytes);
    error(ERR_interrupt, "");

    // keep the compiler happy.  It doesn't know that
    // error() never returns.
    return NULL;
}
