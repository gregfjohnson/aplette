/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

void ex_eps() {
   struct item *p, *q, *r;
   int i, j;
   data d;

   p = fetch2();
   q = sp[-2];
   r = newdat(DA, p->rank, p->size);
   copy(IN, (char *) p->dim, (char *) r->dim, p->rank);
   for(i=0; i<p->size; i++) {
      datum = getdat(p);
      d = zero;
      q->index = 0;
      for(j=0; j<q->size; j++) {
         if(fuzz(getdat(q), datum) == 0) {
            d = one;
            break;
         }
      }
      putdat(r, d);
   }
   pop();
   pop();
   *sp++ = r;
}
