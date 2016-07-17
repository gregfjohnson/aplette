/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "char.h"
#include "data.h"
#include "debug.h"

void ex_asgn()
{
    SymTabEntry* p;
    struct item* q;
    int i;

    p = (SymTabEntry*)sp[-1];
    q = (struct item*)sp[-1]; /* just to get item->index
                               * further down, q is reassigned */
    switch (p->type) {

    case QV:
        i = q->index; /* get the pointer to applicable quad service routine */
        (*exop[i])(1);
        return;

    case LV:
        if (((SymTabEntry*)p->itemp) && ((SymTabEntry*)p)->itemp->type == LBL)
            error(ERR_implicit, "attempt to reassign a label value");
        break;
    default:
        error(ERR, "asgn - panic");
    }

    if (p->use != 0 && p->use != DA)
        error(ERR_domain, "asgn");
    sp--;
    q = fetch1();
    erase(p);
    p->use = DA;
    ((SymTabEntry*)p)->itemp = q;
    sp[-1] = (struct item*)p;

    if (vars_trace)
        vars_dump();
}
