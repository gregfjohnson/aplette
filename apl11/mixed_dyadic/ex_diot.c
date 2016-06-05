/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

void ex_diot() {
   struct item *p, *q, *r;
   int i, j;

   p = fetch2();
   q = sp[-2];
   r = newdat(DA, q->rank, q->size);
   copy(IN, (char *) q->dim, (char *) r->dim, q->rank);
   for(i=0; i<q->size; i++) {
      datum = getdat(q);
      p->index = 0;
      for(j=0; j<p->size; j++) if(fuzz(getdat(p), datum) == 0) break;
      datum = j + iorigin;
      putdat(r, datum);
   }
   pop();
   pop();
   *sp++ = r;
}

