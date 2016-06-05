/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "data.h"

void com1(int k);
void comk(int k);

void ex_com0() {
   fetch2();
   comk(0);
}

void ex_comk() {
   int k;

   k = topfix() - iorigin;
   fetch2();
   comk(k);
}

void ex_com() {
   struct item *q;

   fetch2();
   q = sp[-2];
   comk(q->rank-1);
}

void comk(int k) {
   struct item *p;
   data d;
   int i, dk, ndk;

   p = sp[-1];
   bidx(sp[-2]);

   /* "getdat" returns the value of the data item which
    * it is called to fetch.  If this is non-zero, just
    * use the existing data on the stack (an example in
    * APL would be "x/y" where x != 0.  If this is zero,
    * the result is the null item, which is created by
    * "newdat" and pushed on the stack.
    */

   if(p->rank == 0 || (p->rank == 1 && p->size == 1)){
      if(getdat(p)) {
         pop();
         return;
      }
      p = newdat(idx.type, 1, 0);
      pop();
      pop();
      *sp++ = p;
      return;
   }

   if(idx.rank == 0 && p->rank == 1) {
      /* then scalar right arg ok */
      dk = p->dim[0];
      ndk = 0;
      for (i=0; i<dk; i++) {
         if(getdat(p)) ndk++;
      }
      p = newdat(idx.type, 1, ndk);
      d = getdat(sp[-2]);
      for(i =0; i<ndk; i++) putdat(p,d);
      pop();
      pop();
      *sp++ = p;
      return;
   }
   if(k < 0 || k >= idx.rank) error(ERR_index,"");
   dk = idx.dim[k];
   if(p->rank != 1 || p->size != dk) error(ERR_length,"");
   ndk = 0;
   for(i=0; i<dk; i++) {
      if(getdat(p)) ndk++;
   }
   p = newdat(idx.type, idx.rank, (idx.size/dk)*ndk);
   copy(IN, (char *) idx.dim, (char *) p->dim, idx.rank);
   p->dim[k] = ndk;
   *sp++ = p;
   forloop(com1, k);
   sp--;
   pop();
   pop();
   *sp++ = p;
}

void com1(int k) {
   struct item *p;

   p = sp[-2];
   p->index = idx.idx[k];
   if(getdat(p)) {
      p = sp[-3];
      p->index = access();
      putdat(sp[-1], getdat(p));
   }
}
