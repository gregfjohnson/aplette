/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

int fuzz(data d1, data d2) {
   data f1, f2;

   f1 = d1;
   if(f1 < 0.) f1 = -f1;
   f2 = d2;
   if(f2 < 0.) f2 = -f2;
   if(f2 > f1) f1 = f2;
   f1 *= tolerance;
   if(d1 > d2) {
      if(d2+f1 >= d1) return(0);
      return(1);
   }
   if(d1+f1 >= d2) return(0);
   return(-1);
}

