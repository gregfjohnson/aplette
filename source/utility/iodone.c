/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void iodone(int ok)
{
    item_t* p;

    p = newdat(DA, 0, 1);
    p->datap[0] = ok;
    *expr_stack_ptr++ = p;
}
