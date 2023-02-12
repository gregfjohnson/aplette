/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"

void bidx(item_t* ip)
{
    item_t* p;

    p = ip;
    idx.type = p->itemType;
    idx.rank = p->rank;
    copy(IN, (char*)p->dim, (char*)idx.dim, idx.rank);
    size();
}
