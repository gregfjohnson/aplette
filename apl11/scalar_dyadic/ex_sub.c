/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

data
ex_sub(d1, d2)
data d1, d2;
{
   if(fuzz(d1, d2) == 0) return(zero);
   return(d1 - d2);
}

