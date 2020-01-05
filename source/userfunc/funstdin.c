/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "main.h"
#include "getinput.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "parser.h"
#include "userfunc.h"
#include "work_space.h"

void funstdin() {
    char *p2;
    SymTabEntry *np, *symtabLhsEntry;
    char functionLine[LINEMAX];
    char *linePtr;
    int lineCount;

    pop();

    p2 = compile_old(gsip->text, 2);
    if (p2 == NULL) {
        error(ERR_implicit, "string does not contain a valid function header");
    }

    copy(PTR, (char *) p2 + 1, (char *) &np, 1);
    symtabLhsEntry = symtabFind(np->namep);

    if (symtabLhsEntry == NULL) {
        symtabLhsEntry = symtabInsert(np->namep);
        symtabLhsEntry->entryType = LV;
    }

    sichk(symtabLhsEntry);
    erase(symtabLhsEntry);
    symtabLhsEntry->entryUse = p2[0];

    aplfree((int *) p2);

    symtabLhsEntry->label = 0;

    symtabLhsEntry->functionSourceCode = (char **) alloc(SPTR * 100);

    lineCount = 0;

    linePtr = gsip->text;

    while (1) {
        copy(CH, linePtr, (char *) functionLine, strlen(linePtr)+1);

        symtabLhsEntry->functionSourceCode[lineCount] = (char *) alloc(strlen(linePtr) + 1);
        strcpy(symtabLhsEntry->functionSourceCode[lineCount], linePtr);

        // See if second or subsequent line contains a del character,
        // signaling end of function definition.
        //
        bool done = false;

        if (lineCount > 0) {
            int len = strlen(linePtr);
            for (int i = len-1; i >= 0; --i) {
                if (linePtr[i] == C_DEL) {
                    done = true;
                    break;
                }
            }
        }

        if (lineCount > 0 && ascii_characters) {
            aplfree((int *) linePtr);
        }

        if (done) {
            break;
        }

        char prompt[64] = {0};
        ++lineCount;
        if (isatty(0)) {
            sprintf(prompt, "[%d] ", lineCount);
        }
        linePtr = getinput(prompt);
    }
    symtabLhsEntry->sourceCodeCount = lineCount;
}
