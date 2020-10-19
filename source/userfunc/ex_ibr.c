/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "userfunc.h"

/*
 * monadic interactive branch -- resume function at specific line
 */

void ex_ibr()
{
    Context* thisContext;

    if (state_indicator_ptr == &prime_context || state_indicator_ptr->prev->suspended == 0) {
        error(ERR_implicit, "no suspended fn");
    }

    /* pop current interactive context..
     */
    thisContext = state_indicator_ptr;
    state_indicator_ptr = state_indicator_ptr->prev;
    aplfree(thisContext);

    ex_br();

    if (state_indicator_ptr->expr_stack_ptr == 0 || expr_stack_ptr < state_indicator_ptr->expr_stack_ptr)
        error(ERR_botch, "expr_stack pointer problem");

    while (expr_stack_ptr > state_indicator_ptr->expr_stack_ptr)
        pop();

    longjmp(state_indicator_ptr->env, 0); /* warp out */
}
