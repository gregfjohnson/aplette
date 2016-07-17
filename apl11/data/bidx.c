/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"

void bidx(struct item* ip)
{
    struct item* p;

    p = ip;
    idx.type = p->type;
    idx.rank = p->rank;
    copy(IN, (char*)p->dim, (char*)idx.dim, idx.rank);
    size();
}
