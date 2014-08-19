/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

data
ex_div(d1, d2)
data d1, d2;
{
   /* 0 div 0 is 1 */
   if(d2 == zero) {
      if (d1 == zero) return(one);
      else error(ERR_implicit,"division by 0 attempted");
   }
   return(d1 / d2);
}

