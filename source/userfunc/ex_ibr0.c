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

    if (state_indicator_ptr == &prime_context)
        return;

    if (state_indicator_ptr->prev->suspended == 0) {
        error(ERR_implicit, "no suspended fn");
    }

    /* throw away current context */
    thisContext = state_indicator_ptr->prev;
    aplfree((int*)state_indicator_ptr);
    state_indicator_ptr = thisContext;

    /* un-suspend what was the previous context */
    state_indicator_ptr->suspended = 0;

    /* clear the expr_stack of the previous context */
    while ((state_indicator_ptr->Mode == deffun) && state_indicator_ptr->suspended == 0) {

        if (state_indicator_ptr->expr_stack_ptr == 0 || expr_stack_ptr < state_indicator_ptr->expr_stack_ptr)
            error(ERR_botch, "expr_stack pointer problem");

        while (expr_stack_ptr > state_indicator_ptr->expr_stack_ptr) { pop(); }

        pop();       /* pop off possibly bad previous result */
        ex_nilret(); /* and stick on some dummy datum */

        // find and execute epilog for each function on the expr_stack

        int functionLineLength = state_indicator_ptr->np->functionLineLength;
        Context** lineArray = state_indicator_ptr->np->functionLines;

        state_indicator_ptr->pcode = lineArray[functionLineLength - 1]->pcode;
        state_indicator_ptr->ptr = state_indicator_ptr->pcode;

        execute();

        state_indicator_ptr = state_indicator_ptr->prev;
    }

    /* clear the expr_stack of the original immediate context
    * that led to the suspension
    */
    if (state_indicator_ptr == &prime_context) {
        while (expr_stack_ptr > expr_stack) { pop(); }

        longjmp(cold_restart, 1);
    }
}
