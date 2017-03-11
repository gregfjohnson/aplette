/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void ex_arg2()
{
    struct item *p1, *p2;
    SymTabEntry *np1, *np2;
    SymTabEntry *newEntry1, *newEntry2;

    // get first argument's name
    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np2, 1);

    // skip over ARG1
    gsip->ptr++;

    // get second arg's name
    gsip->ptr += copy(PTR, (char*)gsip->ptr, (char*)&np1, 1);

    // get first expr to be bound to arg
    p1 = fetch(sp[-1]);
    --sp;

    // get second one
    p2 = fetch(sp[-1]);
    --sp;

    *sp++ = (struct item*) np2;
    *sp++ = (struct item*) np1;

    newEntry1 = symtabInsert(np1->namep);
    newEntry2 = symtabInsert(np2->namep);

    // new arg1 binding
    newEntry1->itemp = p1;
    newEntry1->entryType = LV;
    newEntry1->entryUse = DA;

    // ditto arg2
    newEntry2->itemp = p2;
    newEntry2->entryType = LV;
    newEntry2->entryUse = DA;
}
