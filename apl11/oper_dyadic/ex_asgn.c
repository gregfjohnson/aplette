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
    SymTabEntry* symtabLhsEntry;
    int i;

    p = (SymTabEntry*)sp[-1];

    q = (struct item *) sp[-1]; /* just to get item->index
                                 * further down, q is reassigned */

    switch (p->entryType) {
    case QV:
        i = q->index; /* get the pointer to applicable quad service routine */
        (*exop[i])(1);
        return;

    case LV:
        symtabLhsEntry = symtabFind(p->namep);

        if (symtabLhsEntry == NULL) {
            symtabLhsEntry = symtabInsert(p->namep);
        }

        if (symtabLhsEntry != NULL) {
            symtabLhsEntry->entryType = LV;
        }

        if (p->itemp != NULL && p->itemp->itemType == LBL)
            error(ERR_implicit, "attempt to reassign a label value");

        if (symtabLhsEntry == NULL) { error(ERR, "asgn - panic"); }

        break;

    default:
        error(ERR, "asgn - panic");
    }

    if (p->entryUse != UNKNOWN && p->entryUse != DA) { error(ERR_domain, "asgn"); }
    sp--;
    q = fetch1();
    erase(p);
    symtabLhsEntry->entryUse = DA;
    symtabLhsEntry->itemp = q;

    sp[-1] = (struct item*) symtabLhsEntry;

    if (vars_trace) {
        vars_dump();
    }
}
