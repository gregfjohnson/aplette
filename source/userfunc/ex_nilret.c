/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

/* ex_nilret() is called when a user defined function
 * does not return a value.  It just puts an empty vector
 * onto the stack
 */

void ex_nilret()
{
    checksp();
    *sp++ = newdat(NIL, 0, 0);
}
