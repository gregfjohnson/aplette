/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"

/* map used by ex_take ex_drop, ex_rev* and trn0 
 * which is used by ex_dtrn and ex_mtrn 
 */

void map(int o) {
    struct item* p;
    int n, i;

    n = 1;

    for (i = 0; i < idx.rank; i++)
        n *= idx.dim[i];

    p = newdat(idx.type, idx.rank, n);

    copy(IN, (char*)idx.dim, (char*)p->dim, idx.rank);
    *expr_stack_ptr++ = p;

    if (n != 0) {
        struct item* p = expr_stack_ptr[-2];

        indexIterateInit(&idx);
        while (indexIterate(&idx)) {
            p->index = access() + o;
            putdat(expr_stack_ptr[-1], getdat(p));
        }
    }

    expr_stack_ptr--;
    pop();
    *expr_stack_ptr++ = p;
}
