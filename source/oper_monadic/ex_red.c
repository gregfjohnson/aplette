/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdint.h>
#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"

void red0(int k);
void red1(data* dp, item_t* result, data (*f)(data, data));

void ex_red0()
{
    fetch1();
    red0(0);
}

void ex_red()
{
    item_t* p;

    p = fetch1();
    red0(p->rank - 1);
}

void ex_redk()
{
    int i;

    i = topfix() - iorigin;
    fetch1();
    red0(i);
}

void red0(int k)
{
    item_t *p, *q;
    data (*fn)(data, data);

    p = fetch1();

    if (p->itemType != DA)
        error(ERR_domain, "not numeric data");
    bidx(p);
    if (p->rank)
        colapse(k);
    else
        idx.dimk = idx.delk = 1; /* (handcraft for scalars) */
    if (idx.dimk == 0) {
        /*
 *  reduction identities - ets/jrl 5/76
 */
        q = newdat(DA, 0, 1);
        q->dim[0] = 1;
        switch (*state_indicator_ptr->ptr++) {
        case ADD:
        case SUB:
        case OR:
            q->datap[0] = 0;
            break;

        case AND:
        case MUL:
        case DIV:
            q->datap[0] = 1;
            break;

        case MIN:
            q->datap[0] = MAXdata;
            break;

        case MAX:
            q->datap[0] = MINdata;
            break;

        default:
            error(ERR_implicit, "cannot reduce using this function");
        }
        pop();
        *expr_stack_ptr++ = q;
        return;
    }
    fn = (data (*)(data, data))exop[(uint32_t) *state_indicator_ptr->ptr++];

    q = newdat(idx.type, idx.rank, idx.size);
    copy(IN, (char*)idx.dim, (char*)q->dim, idx.rank);

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        red1(p->datap, q, fn);
    }

    pop();
    *expr_stack_ptr++ = q;
}

void red1(data* dp, item_t* result, data (*f)(data, data))
{
    register int i;
    data d;

    dp += access() + (idx.dimk - 1) * idx.delk;
    d = *dp;
    for (i = 1; i < idx.dimk; i++) {
        dp -= idx.delk;
        d = (*f)(*dp, d);
    }
    putdat(result, d);
}
