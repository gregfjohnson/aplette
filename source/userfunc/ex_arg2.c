/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "userfunc.h"

void ex_arg2()
{
    struct item *p1, *p2;
    SymTabEntry *np1, *np2;
    SymTabEntry *newEntry1, *newEntry2;
    SymTabEntry *oldEntry1, *oldEntry2;

    // get first argument's name
    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np2, 1);

    oldEntry2 = symtabFind(np2->namep);
    if (oldEntry2 == NULL) {
        oldEntry2 = symtabEntryCreate(np2->namep);
    }

    // skip over ARG1
    gsip->ptr++;

    // get second arg's name
    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np1, 1);

    oldEntry1 = symtabFind(np1->namep);
    if (oldEntry1 == NULL) {
        oldEntry1 = symtabEntryCreate(np1->namep);
    }

    // get first expr to be bound to arg
    p1 = fetch(sp[-1]);
    --sp;

    // get second one
    p2 = fetch(sp[-1]);
    --sp;

    Context_addShadowedId(gsip, oldEntry2);
    Context_addShadowedId(gsip, oldEntry1);

    symtabRemoveEntry(oldEntry2);
    newEntry2 = symtabInsert(np2->namep);

    symtabRemoveEntry(oldEntry1);
    newEntry1 = symtabInsert(np1->namep);

    // new arg1 binding
    newEntry1->itemp = p1;
    newEntry1->entryUse = DA;

    // ditto arg2
    newEntry2->itemp = p2;
    newEntry2->entryUse = DA;
}
