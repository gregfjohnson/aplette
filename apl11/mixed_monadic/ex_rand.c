/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "apl.h"

double  floor();

data ex_rand(data d) {
   double f;

   f = (random()/(float)INT_MAX) * d;
   d = floor(f) + iorigin;
   return(d);
}
