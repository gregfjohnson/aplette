/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "char.h"
#include "print.h"
#include "mixed_monadic.h"

/*
 * check for latent expr quad LX and evaluate it if found
 */

void eval_qlx()
{
    SymTabEntry* n;
    item_t* p;

    if ((n = nlook(S_QUAD "lx")) && n->itemp->itemType == CH && n->itemp->size) {
        *expr_stack_ptr++ = dupdat(n->itemp);
        sandbox = 1;
        ex_execute();
        sandbox = sandboxflg;
        p = expr_stack_ptr[-1];
        if (p->itemType != EL && p->itemType != NIL)
            ex_print();
        pop();
    }
}
