/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"

void checksp() {
   if(sp >= &stack[STKS]) error(ERR,"stack overflow");
}

