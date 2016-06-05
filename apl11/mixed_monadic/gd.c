/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>

/* gd0 and gd1 are used by both grade up and grade down */

void gd1(int *param[]);

#include "apl.h"
#include "utility.h"
#include "data.h"
#include "memory.h"

void gd0(int k, int (*f)()) {
   struct item *p;
   char *param[2];

   bidx(sp[-1]);
   if(k < 0 || k >= idx.rank) error(ERR_index,"");
   p = newdat(DA, idx.rank, idx.size);
   copy(IN, (char *) idx.dim, (char *) p->dim, idx.rank);
   *sp++ = p;
   colapse(k);
   param[0] = (char *) alloc(idx.dimk*SINT);
   param[1] = (char *)f;
   forloop(gd1, param);
   aplfree((int *) param[0]);
   p = sp[-1];
   sp--;
   pop();
   *sp++ = p;
}

void gd1(int *param[]) {
   struct item *p;
   int i, *m;

   integ = access();
   m = param[0];
   for(i=0; i<idx.dimk; i++) *m++ = i;
   m = param[0];
   qsort(m, idx.dimk, SINT, (int (*)(const void *, const void *)) param[1]);
   p = sp[-1];
   for(i=0; i<idx.dimk; i++) {
      p->index = integ;
      datum = *m++ + iorigin;
      putdat(p, datum);
      integ += idx.delk;
   }
}
