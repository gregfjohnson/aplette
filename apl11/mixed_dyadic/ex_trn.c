/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"


ex_dtrn()
{
   struct item *p, *q;
   int i;

   p = fetch2();
   q = sp[-2];
   if(p->rank > 1 || p->size != q->rank) error(ERR_rank,"");
   for(i=0; i<p->size; i++) idx.idx[i] = fix(getdat(p)) - iorigin;
   pop();
   trn0();
}

ex_mtrn()
{
   struct item *p;
   int i;

   p = fetch1();
   if(p->rank <= 1) return;
   for(i=0; i<p->rank; i++) idx.idx[i] = p->rank-1-i;
   trn0();
}

trn0()
{
   int i, j;
   int d[MRANK], r[MRANK];

   bidx(sp[-1]);
   for(i=0; i<idx.rank; i++) d[i] = -1;
   for(i=0; i<idx.rank; i++) {
      j = idx.idx[i];
      if(j<0 || j>=idx.rank) error(ERR_index,"");
      if(d[j] != -1) {
         if(idx.dim[i] < d[j]) d[j] = idx.dim[i];
         r[j] += idx.del[i];
      }
      else {
         d[j] = idx.dim[i];
         r[j] = idx.del[i];
      }
   }
   j = idx.rank;
   for(i=0; i<idx.rank; i++) {
      if(d[i] != -1) {
         if(i > j) error(ERR_domain,"");
         idx.dim[i] = d[i];
         idx.del[i] = r[i];
      }
      else if(i < j) j = i;
   }
   idx.rank = j;
   map(0);
}

