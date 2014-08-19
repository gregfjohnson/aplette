/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

data
ex_recip(d)
data d;
{
   if(d == zero) error(ERR_domain,"reciprocal of zero attempted");
   return(one/d);
}

