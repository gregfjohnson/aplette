/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"

item_t*
    s2vect(ap) item_t* ap;
{
    item_t *p, *q;

    p = ap;
    q = newdat(p->itemType, 1, 1);
    q->datap = p->datap;
    q->dim[0] = 1;
    return (q);
}
