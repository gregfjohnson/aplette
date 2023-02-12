/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

void revk(int k);

void ex_rev0()
{
    fetch1();
    revk(0);
}

void ex_revk()
{
    int k;

    k = topfix() - iorigin;
    fetch1();
    revk(k);
}

void ex_rev()
{
    item_t* p;

    p = fetch1();
    revk(p->rank - 1);
}

void revk(int k)
{
    int o;

    bidx(expr_stack_ptr[-1]);
    if (k < 0 || k >= idx.rank)
        error(ERR_index, "");
    o = idx.del[k] * (idx.dim[k] - 1);
    idx.del[k] = -idx.del[k];
    map(o);
}
