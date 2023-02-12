/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
double floor();

void ex_rep()
{
    item_t *p, *q, *r;
    double d1, d2, d3;
    data *p1, *p2, *p3;

    p = fetch2();
    q = expr_stack_ptr[-2];
    /*
     * first map 1 element vectors to scalars:
    *
   if(scalar(p)) p->rank = 0;
   if(scalar(q)) q->rank = 0;
    */
    r = newdat(DA, p->rank + q->rank, p->size * q->size);
    copy(IN, (char*)p->dim, (char*)r->dim, p->rank);
    // copy(IN, (char *)q->dim, (char *)(r->dim+p->rank), q->rank);
    copy(IN, (char*)q->dim, (char*)(r->dim + p->rank), q->rank);
    p3 = &r->datap[r->size];
    for (p1 = &p->datap[p->size]; p1 > p->datap;) {
        d1 = *--p1;
        if (d1 == 0.0)
            d1 = 1.0e38; /* all else goes here */
        for (p2 = &q->datap[q->size]; p2 > q->datap;) {
            d2 = *--p2;
            d3 = d2 /= d1;
            *p2 = d2 = floor(d2);
            *--p3 = (d3 - d2) * d1;
        }
    }
    pop();
    pop();
    *expr_stack_ptr++ = r;
}
