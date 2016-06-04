/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"
#include <math.h>

data
ex_fac(d)
data d;
{
   double f;

   f = gamma(d+1.);
   if(f > MAXEXP) error(ERR_limit,"input to factorial function");
   d = exp(f);
   if(signgam < 0) d = -d;         /* if (signgam) in version 6 */
   return(d);
}

