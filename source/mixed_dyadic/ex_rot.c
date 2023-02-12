/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

static void rotk(int k);
static void rot1(int k);

void ex_rot0()
{
    fetch2();
    rotk(0);
}

void ex_rotk()
{
    int k;

    k = topfix() - iorigin;
    fetch2();
    rotk(k);
}

void ex_rot()
{
    item_t* p;

    fetch2();
    p = expr_stack_ptr[-2];
    rotk(p->rank - 1);
}

static void rotk(int k)
{
    item_t* p;
    int isDyadicRotate;

    p = expr_stack_ptr[-1];
    bidx(expr_stack_ptr[-2]);
    if (k < 0 || k >= idx.rank)
        error(ERR_index, "");
    isDyadicRotate = 0;
    colapse(k);
    if (idx.size != p->size) {
        if (p->size != 1)
            error(ERR_length, "");
        isDyadicRotate = 1;
        datum = getdat(p);
    }
    p = newdat(idx.type, 1, idx.dimk);
    *expr_stack_ptr++ = p;

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        rot1(isDyadicRotate);
    }

    pop();
    pop();
}

static void rot1(int k)
{
    item_t *p, *q;
    int i;
    int o, n;

    if (k == 0)
        datum = getdat(expr_stack_ptr[-2]);
    o = fix(datum);
    if (o < 0)
        o = idx.dimk - (-o % idx.dimk);
    q = expr_stack_ptr[-1];
    p = expr_stack_ptr[-3];
    q->index = 0;
    n = access();
    for (i = 0; i < idx.dimk; i++) {
        p->index = n + (o % idx.dimk) * idx.delk;
        putdat(q, getdat(p));
        o++;
    }
    for (i = 0; i < idx.dimk; i++) {
        p->index = n;
        putdat(p, getdat(q));
        n += idx.delk;
    }
}
