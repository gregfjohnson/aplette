/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

void ex_oprod() {
   int i, j;
   data *dp, *dp1, *dp2;
   struct item *p, *q, *r;
   data (*f)();

   f = (data *)exop[*gsip->ptr++];
   p = fetch2();
   q = sp[-2];
   if(p->type != DA || q->type != DA) error(ERR_domain,"not numeric data");
   /*
    * collapse 1 element vectors to scalars
    *
   if(scalar(p)) p->rank = 0;
   if(scalar(q)) q->rank = 0;
   */
   bidx(p);
   for(i=0; i<q->rank; i++) idx.dim[idx.rank++] = q->dim[i];
   r = newdat(DA, idx.rank, size());
   copy(IN, (char *) idx.dim, (char *) r->dim, idx.rank);
   dp = r->datap;
   dp1 = p->datap;
   for(i=0; i<p->size; i++) {
      datum = *dp1++;
      dp2 = q->datap;
      for(j=0; j<q->size; j++) *dp++ = (*f)(datum, *dp2++);
   }
   pop();
   pop();
   *sp++ = r;
}
