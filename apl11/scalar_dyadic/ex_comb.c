/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include <math.h>

data
ex_comb(d1, d2)
data d1, d2;
{
   double f;

   if(d1 > d2) return(zero);
   f = gamma(d2+1.) - gamma(d1+1.) - gamma(d2-d1+1.);
   if(f > MAXEXP) error(ERR_limit,"input range overflow");
   d1 = exp(f);
   return(d1);
}

