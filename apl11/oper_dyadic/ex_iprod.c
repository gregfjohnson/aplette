/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

ex_iprod()
{
   int i, j, param[10], ipr1();
   struct item *p, *q, *r;
   data (*fn)();

   param[0] = exop[*gsip->ptr++];
   param[1] = exop[*gsip->ptr++];
   p = fetch2();
   q = sp[-2];
   if(p->type != DA || q->type != DA) error(ERR_domain,"not numeric data");
   /*
    * extend scalars to match corresponding arg
    */
   if(scalar(p)) {
      if(scalar(q)){
         r = newdat(DA, 0, 1);
         fn = param[1];
         r->datap[0] = (*fn)(p->datap[0], q->datap[0]);
         goto out;
      }
      r = extend(DA, q->dim[0], p->datap[0]);
      pop();
      *sp++ = p = r;
   }
   if(scalar(q)){
      r = extend(DA,p->dim[p->rank - 1], q->datap[0]);
      aplfree(sp[-2]);
      sp[-2] = q = r;
   }
   bidx(p);
   idx.rank--;
   param[2] = idx.dim[idx.rank];
   if((param[2] != q->dim[0])) error(ERR_length,"");
   param[3] = q->size/param[2];
   for(i=1; i<q->rank; i++) idx.dim[idx.rank++] = q->dim[i];
   r = newdat(DA, idx.rank, size());
   copy(IN, idx.dim, r->dim, idx.rank);
   param[4] = 0;
   param[5] = 0;
   param[6] = p->datap;
   param[7] = q->datap;
   param[8] = r->datap;
   param[9] = p->size;
   forloop(ipr1, param);
out:
   pop();
   pop();
   /*
    * KLUDGE (we need the dim[0]'s for above stuff to work)
    */
   if(r->rank == 1 && r->size == 1) r->rank = 0;
   *sp++ = r;
}

ipr1(param)
int param[];
{
   int i, dk, lk, a, b;
   data *dp1, *dp2, *dp3;
   data (*f1)(), (*f2)(), d;

   f1 = param[0];
   f2 = param[1];
   dk = param[2];
   lk = param[3];
   a = param[4];
   b = param[5];
   dp1 = param[6];
   dp2 = param[7];
   dp3 = param[8];
   a += dk;
   b += (dk * lk);
   for(i=0; i<dk; i++) {
      a--;
      b -= lk;
      d = (*f2)(dp1[a], dp2[b]);
      if(i == 0) datum = d;
      else datum = (*f1)(d, datum);
   }
   *dp3++ = datum;
   param[8] = dp3;
   param[5]++;
   if(param[5] >= lk) {
      param[5] = 0;
      param[4] += dk;
      if(param[4] >= param[9]) param[4] = 0;
   }
}

