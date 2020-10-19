/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <strings.h>
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"
#include "userfunc.h"
#include "execute.h"
#include "parser.h"
#include "debug.h"

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

    state_indicator_ptr->ptr += copy(PTR, (char *)state_indicator_ptr->ptr, (char *) &np, 1);

    if (np->functionLines == NULL) {
        funcomp(np);
    }
    lineArray = np->functionLines;

    thisContext = (Context*) alloc(sizeof(Context));
    bzero(thisContext, sizeof(*thisContext));
    thisContext->prev = state_indicator_ptr; /* setup new state indicator */
    thisContext->Mode = deffun;
    thisContext->np = np;
    thisContext->expr_stack_ptr = expr_stack_ptr; /* we can add a more complicated version, later */
    thisContext->funlc = 0;
    thisContext->suspended = 0;
    state_indicator_ptr = thisContext;

    prolgerr = 0; /* Reset error flag */

    functionLineCount = np->functionLineCount;
    functionLineLength = np->functionLineLength;

    checksp();

    if (funtrace) {
        fprintf(stderr, "\ntrace: fn %s entered:\n", np->namep);
    }

    if (setjmp(state_indicator_ptr->env)) {
        // return to here from longjmp()..
        goto reenter;
    } else {
        // fall through to here on initial call to setjmp() above..
    }

    while (1) {
        state_indicator_ptr->funlc++;

        if (funtrace) {
            fprintf(stderr, "\ntrace: fn %s[%d]:\n", np->namep, state_indicator_ptr->funlc - 1);
        }

        if (state_indicator_ptr->funlc == 1) {
            state_indicator_ptr->pcode = lineArray[0]->pcode;

        } else {
            state_indicator_ptr->text = lineArray[state_indicator_ptr->funlc - 1]->text;
            compile_new(CompileFunctionBody);
        }

        execute();

        if (state_indicator_ptr->funlc == 1) {
            state_indicator_ptr->expr_stack_ptr = expr_stack_ptr;
            if (prolgerr) {
                error(ERR_botch, "prolog problem");
            }
        }

        if (intflg) {
            error(ERR_interrupt, "");
        }

        reenter:

        if (state_indicator_ptr->funlc <= 0 || state_indicator_ptr->funlc >= functionLineCount) {
            state_indicator_ptr->funlc = 1; /* for pretty traceback */

            if (funtrace) {
                fprintf(stderr, "\ntrace: fn %s exits\n", np->namep);
                // function_dump(thisContext->np);
            }

            if (vars_trace) {
                fprintf(stderr, "\nsymtab before exit:\n");
                vars_dump();
            }

            state_indicator_ptr->pcode = lineArray[functionLineLength - 1]->pcode;
            execute();

            if (vars_trace) {
                fprintf(stderr, "\nsymtab after exit:\n");
                vars_dump();
            }

            state_indicator_ptr = state_indicator_ptr->prev; /* restore state indicator to previous state */
            aplfree((int*)thisContext);

            return;
        }

        pop();
    }
}
