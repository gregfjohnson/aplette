/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>

/* gd0 and gd1 are used by both grade up and grade down */

static void gd1(int* m, int (*f)(const void*, const void*));

#include "apl.h"
#include "utility.h"
#include "data.h"
#include "memory.h"

void gd0(int k, int (*f)(const void*, const void*))
{
    struct item* p;
    int* intvec;

    bidx(sp[-1]);
    if (k < 0 || k >= idx.rank)
        error(ERR_index, "");
    p = newdat(DA, idx.rank, idx.size);
    copy(IN, (char*)idx.dim, (char*)p->dim, idx.rank);
    *sp++ = p;
    colapse(k);

    intvec = (int*)alloc(idx.dimk * SINT);

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        gd1(intvec, f);
    }

    aplfree(intvec);
    p = sp[-1];
    sp--;
    pop();
    *sp++ = p;
}

static void gd1(int* m, int (*f)(const void*, const void*))
{
    struct item* p;
    int i, *m1;

    integ = access();
    m1 = m;
    for (i = 0; i < idx.dimk; i++)
        *m1++ = i;
    qsort(m, idx.dimk, SINT, (int (*)(const void*, const void*))f);
    p = sp[-1];
    for (i = 0; i < idx.dimk; i++) {
        p->index = integ;
        datum = *m++ + iorigin;
        putdat(p, datum);
        integ += idx.delk;
    }
}
