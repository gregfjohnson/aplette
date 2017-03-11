/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"

static void rav0(int k);
static void rav1(struct item* p, struct item* dest);

void ex_rav()
{
    struct item *p, *r;

    p = fetch1();
    if (p->rank == 0) {
        r = newdat(p->itemType, 1, 1);
        putdat(r, getdat(p));
        pop();
        *sp++ = r;
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
    struct item *p, *r;

    p = sp[-1];
    bidx(p);
    colapse(k);
    r = newdat(p->itemType, 1, p->size);

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        rav1(p, r);
    }

    pop();
    *sp++ = r;
}

static void rav1(struct item* p, struct item* dest)
{
    int i, n;

    n = access();
    for (i = 0; i < idx.dimk; i++) {
        p->index = n;
        putdat(dest, getdat(p));
        n += idx.delk;
    }
}
