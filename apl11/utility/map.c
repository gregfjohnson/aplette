/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

/* map and map1 used by ex_take ex_drop, ex_rev* and trn0 
 * which is used by ex_dtrn and ex_mtrn 
 */
 
map(o)
{
   struct item *p;
   int n, i;
   int map1();

   n = 1;
   for(i=0; i<idx.rank; i++) n *= idx.dim[i];
   if(n == 0) idx.rank == 0;
   p = newdat(idx.type, idx.rank, n);
   copy(IN, idx.dim, p->dim, idx.rank);
   *sp++ = p;
   if(n != 0) forloop(map1, o);
   sp--;
   pop();
   *sp++ = p;
}

map1(o)
{
   struct item *p;

   p = sp[-2];
   p->index = access() + o;
   putdat(sp[-1], getdat(p));
}

