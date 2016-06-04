/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/* gd0 and gd1 are used by both grade up and grade down */

#include "apl.h"
#include "utility.h"
#include "data.h"

gd0(k, f)
int (*f)();
{
   struct item *p;
   char *param[2];
   int gd1();

   bidx(sp[-1]);
   if(k < 0 || k >= idx.rank) error(ERR_index,"");
   p = newdat(DA, idx.rank, idx.size);
   copy(IN, idx.dim, p->dim, idx.rank);
   *sp++ = p;
   colapse(k);
   param[0] = alloc(idx.dimk*SINT);
   param[1] = (char *)f;
   forloop(gd1, param);
   aplfree(param[0]);
   p = sp[-1];
   sp--;
   pop();
   *sp++ = p;
}

gd1(param)
int *param[];
{
   struct item *p;
   int i, *m;

   integ = access();
   m = param[0];
   for(i=0; i<idx.dimk; i++) *m++ = i;
   m = param[0];
   qsort(m, idx.dimk, SINT, param[1]);
   p = sp[-1];
   for(i=0; i<idx.dimk; i++) {
      p->index = integ;
      datum = *m++ + iorigin;
      putdat(p, datum);
      integ += idx.delk;
   }
}
