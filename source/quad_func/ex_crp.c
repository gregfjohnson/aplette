/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"

// quad CR - character representation
// convert a function into a character array

void ex_crp() {
    char name[NAMS], *iline, *c, *c2, *dp;
    SymTabEntry* np;
    struct item* p;
    int len, dim0, dim1, i;
    int lineNumber;

    p = fetch1();
    if (p->size == 0 || p->rank > 1 || p->size >= NAMS)
        error(ERR_length, S_QUAD_ASCII "cr");

    if (p->itemType != CH)
        error(ERR_domain, "");                   // Must be characters

    copy(CH, (char *) p->datap, (char *) name, p->size);
    name[p->size] = '\0';

    np = symtabFind(name);

    // if not found then domain error..
    if (np == NULL || np->namep == NULL)
        error(ERR_domain, S_QUAD_ASCII "cr");

    // if not a function then domain error..
    if (np->entryUse != MF && np->entryUse != DF && np->entryUse != NF) {
        error(ERR_domain, S_QUAD_ASCII "cr");
    }

    // compute max width and height
    dim0 = 0;
    dim1 = 0;

    lineNumber = 0;
    while (1) {
        if (lineNumber >= np->sourceCodeCount) { break; }
        iline = np->functionSourceCode[lineNumber++];

        if (strlen(iline) == 0) { break; }

        c2 = iline;
        while (*c2++ != '\n');
        dim0++;
        len = c2 - iline - 1;
        dim1 = dim1 < len ? len : dim1;
    }

    pop(); // release old variable

    // create new array and put function in
    p = newdat(CH, 2, dim0 * dim1);
    p->rank = 2;
    p->dim[0] = dim0;
    p->dim[1] = dim1;
    dp = (char*)(p->datap);

    lineNumber = 0;
    while (1) {
        if (lineNumber >= np->sourceCodeCount) { break; }
        iline = np->functionSourceCode[lineNumber++];

        if (strlen(iline) == 0) { break; }

        c2 = c = iline;
        for (i = 0; i < dim1; i++) {
            if (*c != '\n')
                *dp++ = *c++;
            else
                *dp++ = ' '; // fill w/blanks
        }
    }

    // put the new array on the expr_stack
    *expr_stack_ptr++ = p;
}
