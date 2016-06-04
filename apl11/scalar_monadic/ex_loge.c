/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"
#include <math.h>

data
ex_loge(d)
data d;
{
   double f;

   f = d;
   if(f <= 0.) error(ERR_limit,"log of negative number attempted");
   d = log(f);
   return(d);
}

