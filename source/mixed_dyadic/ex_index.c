/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"

void ex_elid();
void index1(int i, int f);

void ex_index()
{
    item_t *p, *q;
    int i, j, f, n;

    n = *state_indicator_ptr->ptr++;
    f = *state_indicator_ptr->ptr;
    p = expr_stack_ptr[-1];
    if (f == ASGN) {
        state_indicator_ptr->ptr++;
        if (p->itemType != LV)
            error(ERR_value, "not a local variable");
        if (((SymTabEntry*)p)->entryUse != DA)
            fetch1();
        q = ((SymTabEntry*)p)->itemp;
    }
    else
        q = fetch1();
    if (q->rank != n)
        error(ERR_index, "");
    idx.rank = 0;
    for (i = 0; i < n; i++) {
        p = expr_stack_ptr[-i - 2];
        if (p->itemType == EL) {
            idx.dim[idx.rank++] = q->dim[i];
            continue;
        }
        p = fetch(p);
        expr_stack_ptr[-i - 2] = p;
        for (j = 0; j < p->rank; j++)
            idx.dim[idx.rank++] = p->dim[j];
    }
    size();
    if (f == ASGN) {
        p = fetch(expr_stack_ptr[-n - 2]);
        expr_stack_ptr[-n - 2] = p;
        if (p->size > 1) {
            if (idx.size != p->size)
                error(ERR_length, "");
            f = 1; /* v[i] <- v */

        } else {
            if (idx.size && !p->size)
                error(ERR_length, "");
            /* Note -- for idx.size = 0, no assign occurs
          * anyway, so it is safe to set "datum" to 0
          */
            datum = p->size ? getdat(p) : 0;
            f = 2; /* v[i] <- s */
        }
        ex_elid();

    } else {
        p = newdat(q->itemType, idx.rank, idx.size);
        copy(IN, (char*)idx.dim, (char*)p->dim, idx.rank);
        *expr_stack_ptr++ = p;
        f = 0; /* v[i] */
    }
    bidx(q);
    index1(0, f);
    if (f == 0) {
        p = expr_stack_ptr[-1];
        expr_stack_ptr--;
        for (i = 0; i <= n; i++)
            pop();
        *expr_stack_ptr++ = p;
    }
    else {
        pop(); /* pop ELID */
        expr_stack_ptr--;  /* skip over LV */
        for (i = 0; i < n; i++)
            pop();
    }
}

void ex_elid()
{
    *expr_stack_ptr++ = newdat(EL, 0, 0);
}

void index1(int i, int f)
{
    item_t* p;
    int j, k;

    if (i >= idx.rank) {
        switch (f) {

        case 0:
            p = expr_stack_ptr[-2];
            p->index = access();
            putdat(expr_stack_ptr[-1], getdat(p));
            return;

        case 1:
            datum = getdat(expr_stack_ptr[-idx.rank - 3]);

        case 2:
            p = ((SymTabEntry*)expr_stack_ptr[-2])->itemp;
            p->index = access();
            putdat(p, datum);
            return;
        }
    }
    p = expr_stack_ptr[-i - 3];
    if (p->itemType == EL) {
        for (j = 0; j < idx.dim[i]; j++) {
            idx.idx[i] = j;
            index1(i + 1, f);
        }
        return;
    }
    p->index = 0;
    for (j = 0; j < p->size; j++) {
        k = fix(getdat(p)) - iorigin;
        if (k < 0 || k >= idx.dim[i])
            error(ERR_index, "");
        idx.idx[i] = k;
        index1(i + 1, f);
    }
}
