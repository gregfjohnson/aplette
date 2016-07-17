/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdlib.h>
#include "memory.h"

void afreset()
{
    struct memblock *item, *next_item;

    for (item = firstblock; item; item = next_item) {
        next_item = item->next;
        free(item->block);
        free(item);
    }
    firstblock = 0;
}
