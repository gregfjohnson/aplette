/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
#include "memory.h"
#include "utility.h"

void ipr1(data (*f1)(data, data),
    data (*f2)(data, data),
    int dk,
    int lk,
    int* a,
    int* b,
    int* resultIndex,
    data* dp1,
    data* dp2,
    data* dp3,
    int size);

void ex_iprod()
{
    int i;
    struct item *p, *q, *r;
    data (*fnleft)(data, data);
    data (*fnright)(data, data);
    int commonDimension;
    int a = 0, b = 0, resultIndex = 0;

    fnleft = exop[*gsip->ptr++];
    fnright = exop[*gsip->ptr++];

    p = fetch2();
    q = sp[-2];

    if (p->type != DA || q->type != DA)
        error(ERR_domain, "not numeric data");

    // extend scalars to match corresponding arg
    if (scalar(p)) {
        if (scalar(q)) {
            r = newdat(DA, 0, 1);
            r->datap[0] = (*fnright)(p->datap[0], q->datap[0]);
            goto out;
        }
        r = extend(DA, q->dim[0], p->datap[0]);
        pop();
        *sp++ = p = r;
    }

    if (scalar(q)) {
        r = extend(DA, p->dim[p->rank - 1], q->datap[0]);
        aplfree((int*)sp[-2]);
        sp[-2] = q = r;
    }

    bidx(p);
    commonDimension = idx.dim[idx.rank - 1];
    idx.rank--;

    if (commonDimension != q->dim[0]) {
        error(ERR_length, "");
    }

    for (i = 1; i < q->rank; i++) {
        if (idx.rank >= MRANK) {
            error(ERR_limit, "");
        }
        idx.dim[idx.rank++] = q->dim[i];
    }

    r = newdat(DA, idx.rank, size());

    copy(IN, (char*)idx.dim, (char*)r->dim, idx.rank);

    indexIterateInit(&idx);

    while (indexIterate(&idx)) {
        ipr1(fnleft,
            fnright,
            commonDimension,
            q->size / commonDimension,
            &a,
            &b,
            &resultIndex,
            p->datap,
            q->datap,
            r->datap,
            p->size);
    }
out:
    pop();
    pop();
    /*
    * KLUDGE (we need the dim[0]'s for above stuff to work)
    */
    if (r->rank == 1 && r->size == 1)
        r->rank = 0;
    *sp++ = r;
}

void ipr1(data (*f1)(data, data),
    data (*f2)(data, data),
    int dk,
    int lk,
    int* a,
    int* b,
    int* resultIndex,
    data* dp1,
    data* dp2,
    data* dp3,
    int size)
{
    int i;
    data d;

    *a += dk;
    *b += (dk * lk);

    for (i = 0; i < dk; i++) {
        *a -= 1;
        *b -= lk;
        d = (*f2)(dp1[*a], dp2[*b]);

        if (i == 0)
            datum = d;
        else
            datum = (*f1)(d, datum);
    }

    dp3[*resultIndex] = datum;
    *resultIndex += 1;

    *b += 1;
    if (*b >= lk) {
        *b = 0;

        *a += dk;
        if (*a >= size) {
            *a = 0;
        }
    }
}
