/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

data
ex_min(d1, d2)
data d1, d2;
{
   if(d1 < d2) return(d1);
   return(d2);
}

