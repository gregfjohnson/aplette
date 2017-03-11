/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "execute.h"
#include "userfunc.h"

/*
 * immediate niladic branch -- reset SI
 */

void ex_ibr0()
{
    Context* thisContext;
    int* p;

    if (gsip == &prime_context)
        return;

    if (gsip->prev->suspended == 0) {
        error(ERR_implicit, "no suspended fn");
    }

    /* throw away current context */
    thisContext = gsip->prev;
    aplfree((int*)gsip);
    gsip = thisContext;

    /* un-suspend what was the previous context */
    gsip->suspended = 0;

    /* clear the stack of the previous context */
    while ((gsip->Mode == deffun) && gsip->suspended == 0) {

        if (gsip->sp == 0 || sp < gsip->sp)
            error(ERR_botch, "stack pointer problem");

        while (sp > gsip->sp) { pop(); }

        pop();       /* pop off possibly bad previous result */
        ex_nilret(); /* and stick on some dummy datum */

        // find and execute epilog for each function on the stack

        int functionLineLength = gsip->np->functionLineLength;
        Context** lineArray = gsip->np->functionLines;

        gsip->pcode = lineArray[functionLineLength - 1]->pcode;
        gsip->ptr = gsip->pcode;

        execute();

        gsip = gsip->prev;
    }

    /* clear the stack of the original immediate context
    * that led to the suspension
    */
    if (gsip == &prime_context) {
        while (sp > stack) { pop(); }

        longjmp(cold_restart, 1);
    }
}
