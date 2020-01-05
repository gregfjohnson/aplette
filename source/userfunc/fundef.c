/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "memory.h"
#include "work_space.h"
#include "userfunc.h"
#include "parser.h"
#include "main.h"
#include "utility.h"

static int copyFile(char ***lines, FILE *f);

/*
 * fundef - defines a function
 * Once a file has been edited by the user, this routine
 * will read into the workspace file.  It will also attempt
 * a compile of just the header and return an error if
 * the parser cannot use it.
 *
 * It uses a mix of buffered and nonbuf IO.
 */

int fundef(int f) {
    char *iline = NULL, *c;
    SymTabEntry* np;
    SymTabEntry* symtabLhsEntry;
    FILE* infile;
    char *status;

    infile = fdopen(f, "r");

    iline = (char *) alloc(LINEMAX);

    status = readLine("fundef verify first line", iline, LINEMAX, infile);

    if (status == NULL || 0 == strcmp(iline, "\n")) {
        printf("Blank function header. \n");
        goto out;
    }

    c = compile_old(iline, CompileFunctionDefn);

    if (c == 0)
        goto out;

    copy(PTR, (char*)c + 1, (char*)&np, 1);
    symtabLhsEntry = symtabFind(np->namep);

    if (symtabLhsEntry == NULL) {
        symtabLhsEntry = symtabInsert(np->namep);
        symtabLhsEntry->entryType = LV;
    }

    sichk(symtabLhsEntry);
    erase(symtabLhsEntry);
    symtabLhsEntry->entryUse = c[0];

    aplfree((int *) c);

    // we save the source code of the function into the function
    // symbol table entry.
    //
    // we lazily compile, and only get around to compiling a function
    // that has been read in the first time it actually gets used.
    //
    // this is for mutual recursion.  and, simply, a function whose
    // body refers to a not-yet-defined function.
    // for parsing, we need to know
    // the arity of every identifier, but nothing else.
    //
    // if we compile just function headers and not bodies, we
    // will have the arities of the function names.  Then, when
    // we get around to executing a function, we can compile the
    // body lines, because we know the arity of other functions.
    //

    symtabLhsEntry->label = 0;

    symtabLhsEntry->sourceCodeCount =
            copyFile(&symtabLhsEntry->functionSourceCode, infile);

out:
    if (iline != NULL) {
        aplfree((int *) iline);
    }

    fclose(infile);

    return 1;
}

static int copyFile(char ***lines, FILE *f) {
    char *iline;
    int lineCount = 0;

    *lines = NULL;

    iline = (char *) alloc(LINEMAX);

    fseek(f, 0L, SEEK_SET);
    while (readLine("copyFile", iline, LINEMAX, f)) {
        ++lineCount;
    }
    if (lineCount == 0) { return 0; }

    fseek(f, 0L, SEEK_SET);

    *lines = (char **) alloc(SPTR * lineCount);
    lineCount = 0;
    while (readLine("copyFile", iline, LINEMAX, f)) {
        (*lines)[lineCount] = (char *) alloc(strlen(iline) + 1);
        strcpy((*lines)[lineCount], iline);

        ++lineCount;
    }

    return lineCount;
}
