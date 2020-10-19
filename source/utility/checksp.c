/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"

void checksp()
{
    if (expr_stack_ptr >= &expr_stack[STKS])
        error(ERR, "expr_stack overflow");
}
