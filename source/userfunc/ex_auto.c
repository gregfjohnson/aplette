/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "userfunc.h"

void ex_auto()
{
    SymTabEntry* np;
    SymTabEntry* oldEntry;

    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np, 1);

    oldEntry = symtabFind(np->namep);
    if (oldEntry == NULL) {
        oldEntry = symtabEntryCreate(np->namep);
    }

    checksp();

    Context_addShadowedId(gsip, oldEntry);

    symtabRemoveEntry(oldEntry);

    symtabInsert(np->namep);
}
