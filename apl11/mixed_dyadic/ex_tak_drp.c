/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>

#include "apl.h"
#include "utility.h"
#include "data.h"

int td1(int tdmode);
void takezr(int* fill);

void ex_take()
{
    int i, k, o, fill[MRANK], fflg;

    /* While TANSTAAFL, in APL there is a close approximation.  It
    * is possible to perform a "take" of more elements than an
    * array actually contains (to be padded with zeros or blanks).
    * If "td1()" detects that a dimension exceeds what the array
    * actually contains it will return 1.  Special code is then
    * required to force the extra elements in the new array to
    * zero or blank.  This code is supposed to work for null items
    * also, but it doesn't.
    */

    o = 0;
    fflg = td1(0);
    for (i = 0; i < idx.rank; i++) {
        fill[i] = 0;
        k = idx.idx[i];
        if (k < 0) {
            k = -k;
            if (k > idx.dim[i])
                fill[i] = idx.dim[i] - k;
            o += idx.del[i] * (idx.dim[i] - k);
        }
        else {
            if (k > idx.dim[i])
                fill[i] = idx.dim[i];
        }
        idx.dim[i] = k;
    }
    map(o);

    if (fflg) {
        bidx(sp[-1]);
        indexIterateInit(&idx);
        while (indexIterate(&idx)) {
            takezr(fill);
        }
    }
}

void ex_drop()
{
    int i, k, o;

    o = 0;
    td1(1);
    for (i = 0; i < idx.rank; i++) {
        k = idx.idx[i];
        if (k > 0)
            o += idx.del[i] * k;
        else
            k = -k;
        idx.dim[i] -= k;
    }
    map(o);
}

int td1(int tdmode)
{
    struct item *p, *q, *nq, *s2vect();
    int i, k;
    int r; /* set to 1 if take > array dim */

    p = fetch2();
    q = sp[-2];
    r = !q->size;       /* Weird stuff for null items */
    if (q->rank == 0) { /* Extend scalars */
        nq = newdat(q->type, p->size, 1);
        *nq->datap = *q->datap;
        pop();
        *sp++ = q = nq;
        for (i = 0; i < p->size; i++)
            q->dim[i] = 1;
    }
    if (p->rank > 1 || q->rank != p->size)
        error(ERR_rank, "");
    bidx(q);
    for (i = 0; i < p->size; i++) {
        k = fix(getdat(p));
        idx.idx[i] = k;
        if (k < 0)
            k = -k;

        /* If an attempt is made to drop more than what
       * exists, modify the drop to drop exactly what
       * exists.
       */

        if (k > idx.dim[i]) {
            if (tdmode)
                idx.idx[i] = idx.dim[i];
            else
                r = 1;
        }
    }
    pop();
    return (r);
}

void takezr(int* fill)
{
    struct item* p;
    int i;

    for (i = 0; i < idx.rank; i++) {
        if ((fill[i] > 0 && idx.idx[i] >= fill[i]) || (fill[i] < 0 && idx.idx[i] < -fill[i])) {
            p = sp[-1];
            p->index = access();
            putdat(p, (p->type == DA) ? zero : (data)' ');
            return;
        }
    }
}
