/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "main.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "parser.h"
#include "userfunc.h"
#include "work_space.h"

void ex_fdef() {
    struct item *p;
    char *iline, *p2;
    SymTabEntry *np, *symtabLhsEntry;
    char functionLine[LINEMAX];
    int dim0, dim1;
    char *lineStart;
    int lineCount;

    p = fetch1();

    if (p->rank != 2 && p->rank != 1)
        error(ERR_rank, "");

    if (p->itemType != CH)
        error(ERR_domain, "");

    /* The following code has been commented out as a
    * test of slight modifications to the compiler.
    * Before this change, it was impossible to use quad-FX
    * from inside an APL function, for it might damage
    * an existing function by the same name.  The compiler
    * now checks when processing function headers to see
    * if the function is suspended by calling "sichk", which
    * will generate an error if so.  Hopefully this will now
    * allow quad-FX to be used freely without disastrous side-
    * effects.
    *
   if(gsip) error(ERR,"si damage -- type ')sic'");
    */

    dim0 = p->dim[0];
    dim1 = p->dim[1];
    if (p->rank == 1) { dim1 = dim0; }

    copy(CH, (char*)p->datap, (char *) functionLine, dim1);
    functionLine[dim1] = '\n';

    if (ascii_characters) {
        iline = to_ascii_input(functionLine);
    } else {
        iline = functionLine;
    }

    p2 = compile_old(iline, CompileFunctionDefn);
    if (p2 == NULL) {
        error(ERR_implicit, "string does not contain a valid function header");
    }

    if (ascii_characters) { aplfree(iline); }

    copy(PTR, (char *) p2 + 1, (char *) &np, 1);
    symtabLhsEntry = symtabFind(np->namep);

    if (symtabLhsEntry == NULL) {
        symtabLhsEntry = symtabInsert(np->namep);
        symtabLhsEntry->itemType = LV;
    }

    sichk(symtabLhsEntry);
    erase(symtabLhsEntry);
    symtabLhsEntry->entryUse = p2[0];

    aplfree((int *) p2);

    symtabLhsEntry->label = 0;

    symtabLhsEntry->functionSourceCode = (char **) alloc(SPTR * dim0);

    lineStart = (char *) p->datap;
    for (lineCount = 0; lineCount < dim0; ++lineCount) {
        int i;

        copy(CH, lineStart, (char *) functionLine, dim1);

        for (i = dim1-1; i >= 0; --i) {
            if (functionLine[i] != ' ') { break; }
        }

        functionLine[i+1] = '\n';
        functionLine[i+2] = '\0';

        if (ascii_characters) {
            iline = to_ascii_input(functionLine);

        } else {
            iline = functionLine;
        }

        symtabLhsEntry->functionSourceCode[lineCount] = (char *) alloc(strlen(iline) + 1);
        strcpy(symtabLhsEntry->functionSourceCode[lineCount], iline);

        if (ascii_characters) {
            aplfree((int *) iline);
        }

        lineStart += dim1;
    }
    symtabLhsEntry->sourceCodeCount = lineCount;

    pop();
    *sp++ = newdat(DA, 1, 0);
}
