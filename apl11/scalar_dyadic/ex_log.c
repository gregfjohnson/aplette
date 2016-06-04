/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"
#include <math.h>

data
ex_log(d1, d2)
data d1, d2;
{
   double f1, f2;

   f1 = d1;
   f2 = d2;
   if(f1 <= 0. || f2 <= 0.) 
      error(ERR_implicit,"log of a negative number attempted");
   d1 = log(f2)/log(f1);
   return(d1);
}

