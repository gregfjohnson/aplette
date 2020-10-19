/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/* expand:  1 0 1 0 1 \ I3
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

void exd1(int k);
void exdk(int k);

void ex_exd0()
{
    fetch2();
    exdk(0);
}

void ex_exdk()
{
    int k;

    k = topfix() - iorigin;
    fetch2();
    exdk(k);
}

void ex_exd()
{
    struct item* q;

    fetch2();
    q = expr_stack_ptr[-2];
    exdk(q->rank - 1);
}

void exdk(int k)
{
    struct item* p;
    int i, dk;

    p = expr_stack_ptr[-1];
    bidx(expr_stack_ptr[-2]);
    if (k < 0 || k >= idx.rank)
        error(ERR_index, "");
    dk = 0;
    for (i = 0; i < p->size; i++)
        if (getdat(p))
            dk++;
    if (p->rank != 1 || dk != idx.dim[k])
        error(ERR_length, "");
    idx.dim[k] = p->size;
    size();
    p = newdat(idx.type, idx.rank, idx.size);
    copy(IN, (char*)idx.dim, (char*)p->dim, idx.rank);
    *expr_stack_ptr++ = p;

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        exd1(k);
    }

    expr_stack_ptr--;
    pop();
    pop();
    *expr_stack_ptr++ = p;
}

void exd1(int k)
{
    struct item* p;

    p = expr_stack_ptr[-2];
    p->index = idx.idx[k];
    if (getdat(p))
        datum = getdat(expr_stack_ptr[-3]);
    else if (idx.type == DA)
        datum = zero;
    else
        datum = ' ';
    putdat(expr_stack_ptr[-1], datum);
}
