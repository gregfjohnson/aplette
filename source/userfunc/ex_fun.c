/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"
#include "userfunc.h"
#include "execute.h"
#include "parser.h"

int prolgerr; /* Flag -- set if bad fetch in prologue 
                    * this variable is global so that fetch()
                    * is able to set it */

void ex_fun()
{
    SymTabEntry* np;
    int functionLineCount;
    int functionLineLength;
    Context** lineArray;
    Context* thisContext;
    Context* savedGsip;

    gsip->ptr += copy(PTR, (char *)gsip->ptr, (char *) &np, 1);

    if (np->functionLines == NULL) {
        funcomp(np);
    }
    lineArray = np->functionLines;

    thisContext = (Context*) alloc(sizeof(Context));
    thisContext->prev = gsip; /* setup new state indicator */
    thisContext->Mode = deffun;
    thisContext->np = np;
    thisContext->sp = sp; /* we can add a more complicated version, later */
    thisContext->funlc = 0;
    thisContext->suspended = 0;
    gsip = thisContext;

    prolgerr = 0; /* Reset error flag */

    functionLineCount = np->functionLineCount;
    functionLineLength = np->functionLineLength;

    checksp();

    if (funtrace) {
        fprintf(stderr, "\ntrace: fn %s entered:\n", np->namep);
    }

    if (setjmp(gsip->env)) {
        goto reenter;
    }

    while (1) {
        gsip->funlc++;

        if (funtrace) {
            fprintf(stderr, "\ntrace: fn %s[%d]:\n", np->namep, gsip->funlc - 1);
        }

        if (gsip->funlc == 1) {
            gsip->pcode = lineArray[0]->pcode;

        } else {
            gsip->text = lineArray[gsip->funlc - 1]->text;
            compile_new(CompileFunctionBody);
        }

        execute();

        if (gsip->funlc == 1) {
            gsip->sp = sp;
            if (prolgerr) {
                error(ERR_botch, "prolog problem");
            }
        }

        if (intflg) {
            error(ERR_interrupt, "");
        }

        reenter:

        if (gsip->funlc <= 0 || gsip->funlc >= functionLineCount) {
            gsip->funlc = 1; /* for pretty traceback */

            if (funtrace) {
                fprintf(stderr, "\ntrace: fn %s exits\n", np->namep);
                // function_dump(thisContext->np);
            }

            if (vars_trace) {
                fprintf(stderr, "\nsymtab before exit:\n");
                vars_dump();
            }

            gsip->pcode = lineArray[functionLineLength - 1]->pcode;
            execute();

            if (vars_trace) {
                fprintf(stderr, "\nsymtab after exit:\n");
                vars_dump();
            }

            gsip = gsip->prev; /* restore state indicator to previous state */
            aplfree((int*)thisContext);

            return;
        }

        pop();
    }
}
