/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

int   gdd();

void ex_gdd() {
   struct item *p;

   p = fetch1();
   gd0(p->rank-1, gdd);
}

void ex_gddk() {
   int k;

   k = topfix() - iorigin;
   fetch1();
   gd0(k, gdd);
}

int gdd(int *p1, int *p2) {
   struct item *p;
   data d1, d2;

   p = sp[-2];
   p->index = integ + *p1 * idx.delk;
   d1 = getdat(p);
   p->index = integ + *p2 * idx.delk;
   d2 = getdat(p);
   if(fuzz(d1, d2) != 0) {
      if(d1 > d2) return(-1);
      return(1);
   }
   return(*p1 - *p2);
}
