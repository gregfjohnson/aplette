/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"

struct item* dupdat(struct item* ap) {
    struct item *p1, *p2;
    int i;

    p1 = ap;
    p2 = newdat(p1->itemType, p1->rank, p1->size);
    for (i = 0; i < p1->rank; i++)
        p2->dim[i] = p1->dim[i];
    copy(p1->itemType, (char*)p1->datap, (char*)p2->datap, p1->size);
    return (p2);
}
