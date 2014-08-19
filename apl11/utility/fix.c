/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
double  floor();

fix(d)
data d;
{
   int i;

   i = floor(d+0.5);
   return(i);
}

