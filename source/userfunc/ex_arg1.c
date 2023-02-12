/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "userfunc.h"

void ex_arg1() {
    item_t* p;
    SymTabEntry* np;
    SymTabEntry* oldEntry;
    SymTabEntry* newEntry;

    state_indicator_ptr->ptr += copy(PTR, (char*) state_indicator_ptr->ptr, (char*) &np, 1);

    oldEntry = symtabFind(np->namep);
    if (oldEntry == NULL) {
        oldEntry = symtabEntryCreate(np->namep);
    }

    p = fetch(expr_stack_ptr[-1]);
    --expr_stack_ptr;

    Context_addShadowedId(state_indicator_ptr, oldEntry);

    symtabRemoveEntry(oldEntry);
    newEntry = symtabInsert(np->namep);

    newEntry->itemp = p;
    newEntry->entryUse = DA;
}
