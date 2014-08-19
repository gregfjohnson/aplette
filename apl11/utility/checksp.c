/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
/* #include <stdio.h> */
#include "apl.h"

checksp()
{
   if(sp >= &stack[STKS]) error(ERR,"stack overflow");
}

