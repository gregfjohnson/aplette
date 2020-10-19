/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "memory.h"
#include "data.h"

void clear()
{
    symtab_clear();

    afreset(); /* release all dynamic memory */
    state_indicator_ptr = 0;  /* reset state indicator */

    iorigin = INITIAL_iorigin;
    pagewidth = INITIAL_pagewidth;
    PrintP = INITIAL_PrintP;
    tolerance = INITIAL_tolerance;
}
