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
    struct item* p;

    if ((n = nlook(S_QUAD "lx")) && n->itemp->type == CH && n->itemp->size) {
        *sp++ = dupdat(n->itemp);
        sandbox = 1;
        ex_execute();
        sandbox = sandboxflg;
        p = sp[-1];
        if (p->type != EL && p->type != NIL)
            ex_print();
        pop();
    }
}
