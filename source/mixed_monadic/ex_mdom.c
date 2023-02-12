/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"
#include "mixed_dyadic.h"

void ex_mdom()
{
    data* dp;
    int a, i, j;
    item_t *p, *q;

    p = fetch1();
    if (p->rank != 2)
        error(ERR_rank, "");
    a = p->dim[0];
    q = newdat(DA, 2, a * a);
    q->dim[0] = a;
    q->dim[1] = a;
    *expr_stack_ptr++ = q;
    dp = q->datap;
    for (i = 0; i < a; i++) {
        for (j = 0; j < a; j++) {
            datum = zero;
            if (i == j)
                datum = one;
            *dp++ = datum;
        }
    }
    ex_ddom();
}
