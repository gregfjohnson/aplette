/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void ex_arg1() {
    struct item* p;
    SymTabEntry* np;
    SymTabEntry* newEntry;

    gsip->ptr += copy(PTR, (char*) gsip->ptr, (char*) &np, 1);
    p = fetch(sp[-1]);
    --sp;

    *sp++ = (struct item*) np;

    symtabRemoveEntry(np);
    newEntry = symtabInsert(np->namep);

    newEntry->itemp = p;
    newEntry->entryType = LV;
    newEntry->entryUse = DA; // ???
}
