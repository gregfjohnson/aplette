/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"

void ex_auto()
{
    SymTabEntry* np;
    SymTabEntry* newEntry;

    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np, 1);
    checksp();

    *sp++ = (struct item*) np;
    symtabRemoveEntry(np);

    newEntry = symtabInsert(np->namep);
    newEntry->entryType = LV;
}
