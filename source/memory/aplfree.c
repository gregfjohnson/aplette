/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "memory.h"

void aplfree(int* ap)
{
    struct memblock *item, *last;

    if (ap == 0)
        return;

    last = 0;
    for (item = firstblock; item; item = item->next) {
        if (item->block == ap) {
            if (last)
                last->next = item->next;
            else
                firstblock = item->next;

            if (mem_trace) {
                printf("[aplfree: %d bytes at %p (data)",
                    item->nbytes, (void *) item->block);
            }
            free(item->block);

            if (mem_trace) {
                printf(", %ld bytes at %p (memblock)]\n",
                    sizeof(struct memblock), (void *) item);
            }
            free(item);
            return;
        }
        last = item;
    }
    printf("aplfree bad block address %p\n", (void *) ap);
}
