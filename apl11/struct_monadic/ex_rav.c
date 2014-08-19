/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
ex_rav()
{
   struct item *p, *r;

   p = fetch1();
   if(p->rank == 0) {
      r = newdat(p->type, 1, 1);
      putdat(r, getdat(p));
      pop();
      *sp++ = r;
      return;
   }
   rav0(p->rank-1);
}

ex_ravk()
{
   int i;

   i = topfix() - iorigin;
   fetch1();
   rav0(i);
}

rav0(k)
{
   struct item *p, *r, *param[2];
   int rav1();

   p = sp[-1];
   bidx(p);
   colapse(k);
   r = newdat(p->type, 1, p->size);
   param[0] = p;
   param[1] = r;
   forloop(rav1, param);
   pop();
   *sp++ = r;
}

rav1(param)
struct item *param[];
{
   struct item *p;
   int i, n;

   p = param[0];
   n = access();
   for(i=0; i<idx.dimk; i++) {
      p->index = n;
      putdat(param[1], getdat(p));
      n += idx.delk;
   }
}

