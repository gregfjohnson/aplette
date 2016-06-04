/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

ex_cat()
{
   struct item *p, *q, *r;
   int k;

   p = fetch2();
   q = sp[-2];
   k = p->rank;
   if(p->type != q->type) error(ERR_domain,"");
   if(q->rank > k) k = q->rank;
   if(k == 0) {
      r = newdat(p->type, 1, 2);
      putdat(r, getdat(p));
      putdat(r, getdat(q));
      pop();
      pop();
      *sp++ = r;
   }
   else cat0(k-1);
}

ex_catk()	//cat along index [k]
{
   int k;
   double d, top();

   d = top();	//obtain k
   k = fix(d);
   fetch2();
   if (0 == fuzz(d, (double)k)) cat0(k-iorigin);
   else lam0(d);
}

cat0(k)
{
   struct item *p, *q, *r;
   int i, a, b;

   p = sp[-1];
   q = sp[-2];
   i = k;
   if(p->type != q->type) error(ERR_domain,"");
   if(p->rank >=  q->rank) {
      bidx(p);
      b = cat1(q, i);
      a = idx.dim[i];
   }
   else {
      bidx(q);
      a = cat1(p, i);
      b = idx.dim[i];
   }
   idx.dim[i] = a+b;
   size();
   r = newdat(p->type, idx.rank, idx.size);
   copy(IN, idx.dim, r->dim, idx.rank);
   i = idx.del[i];
   a *= i;
   b *= i;
   while(r->index < r->size) {
      for(i=0; i<a; i++) putdat(r, getdat(p));
      for(i=0; i<b; i++) putdat(r, getdat(q));
   }
   pop();
   pop();
   *sp++ = r;
}

cat1(ip, k)
struct item *ip;
{
   struct item *p;
   int i, j, a;

   if(k < 0 || k >= idx.rank) error(ERR_index,"");
   p = ip;
   a = 1;
   if(p->rank == 0) return(a);
   j = 0;
   for(i=0; i<idx.rank; i++) {
      if(i == k) {
         if(p->rank == idx.rank) {
            a = p->dim[i];
            j++;
         }
         continue;
      }
      if(idx.dim[i] != p->dim[j]) error(ERR_length,"sizes do not match");
      j++;
   }
   return(a);
}

lam0(d)		//laminate, similar to catenate but create a new dimension
double d;
{
   struct item *p, *q, *r;
   int i, j, k;

   p = sp[-1];
   q = sp[-2];
   if(p->type != q->type) error(ERR_domain,"");
   if (q->rank > p->rank) p = q;
   if (p->rank >= MRANK) error(ERR_rank,"");
   idx.type = p->type;
   idx.rank = p->rank + 1;
   k = fix(d) - iorigin;
   if (k < 0 || k >= p->rank+1) error(ERR_index,"");
   j = 0;
   for (i=0; i<p->rank; i++) {
      if (i == k) idx.dim[j++] = 1;
      idx.dim[j++] = p->dim[i];
   }
   if (i == k) idx.dim[j] = 1;
   size();
   r = newdat(idx.type, idx.rank, idx.size);
   copy(IN, idx.dim, r->dim, idx.rank);
   copy(idx.type, p->datap, r->datap, r->size);
   if (p == sp[-1]) sp[-1] = r;
   else sp[-2] = r;
   aplfree(p);
   cat0(k);
}
