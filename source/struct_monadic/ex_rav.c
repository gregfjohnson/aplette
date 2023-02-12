/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"

static void rav0(int k);
static void rav1(item_t* p, item_t* dest);

void ex_rav()
{
    item_t *p, *r;

    p = fetch1();
    if (p->rank == 0) {
        r = newdat(p->itemType, 1, 1);
        putdat(r, getdat(p));
        pop();
        *expr_stack_ptr++ = r;
        return;
    }
    rav0(p->rank - 1);
}

void ex_ravk()
{
    int i;

    i = topfix() - iorigin;
    fetch1();
    rav0(i);
}

static void rav0(int k)
{
    item_t *p, *r;

    p = expr_stack_ptr[-1];
    bidx(p);
    colapse(k);
    r = newdat(p->itemType, 1, p->size);

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        rav1(p, r);
    }

    pop();
    *expr_stack_ptr++ = r;
}

static void rav1(item_t* p, item_t* dest)
{
    int i, n;

    n = access();
    for (i = 0; i < idx.dimk; i++) {
        p->index = n;
        putdat(dest, getdat(p));
        n += idx.delk;
    }
}
