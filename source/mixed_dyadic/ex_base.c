/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "opt_codes.h"
#include "oper_dyadic.h"

char base_com[] = { ADD, MUL };

void ex_base()
{
    struct item* extend();
    struct item *p, *q;
    int i;
    char* savptr;
    data d1, d2;

    p = fetch2();
    q = expr_stack_ptr[-2];
    if (p->itemType != DA || q->itemType != DA)
        error(ERR_domain, "base - incorrect types");
    if (p->rank > 1)
        error(ERR_rank, "base - cannot handle left-arg-rank > 1");
    if (scalar(p)) {
        if (q->rank > 0)
            i = q->dim[0];
        else
            i = q->size;
        q = extend(DA, i, p->datap[0]);
        pop();
        *expr_stack_ptr++ = p = q;
        q = expr_stack_ptr[-2];
    }
    d1 = p->datap[p->size - 1];
    p->datap[p->size - 1] = 1.0;
    for (i = p->size - 2; i >= 0; i--) {
        d2 = p->datap[i];
        p->datap[i] = d1;
        d1 *= d2;
    }
    savptr = state_indicator_ptr->ptr;
    state_indicator_ptr->ptr = base_com;
    ex_iprod();
    state_indicator_ptr->ptr = savptr;
}
