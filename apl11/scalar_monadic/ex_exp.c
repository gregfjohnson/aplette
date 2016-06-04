/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"
#include <math.h>

data
ex_exp(d)
data d;
{
   double f;

   f = d;
   if(f > MAXEXP) error(ERR_limit,"input value to exp function");
   d = exp(f);
   return(d);
}

