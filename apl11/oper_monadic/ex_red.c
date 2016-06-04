/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"

ex_red0()
{
   fetch1();
   red0(0);
}

ex_red()
{
   struct item *p;

   p = fetch1();
   red0(p->rank-1);
}

ex_redk()
{
   int i;

   i = topfix() - iorigin;
   fetch1();
   red0(i);
}

red0(k)
{
   struct item *p, *q;
   int param[3], red1();

   p = fetch1();
   if(p->type != DA) error(ERR_domain,"not numeric data");
   bidx(p);
   if (p->rank) colapse(k);
   else idx.dimk = idx.delk = 1;  /* (handcraft for scalars) */
   if(idx.dimk == 0) {
/*
 *  reduction identities - ets/jrl 5/76
 */
      q = newdat(DA,0,1);
      q->dim[0] = 1;
      switch(*gsip->ptr++) {
         case ADD:
         case SUB:
         case OR:
         q->datap[0] = 0;
         break;

         case AND:
         case MUL:
         case DIV:
         q->datap[0] = 1;
         break;

         case MIN:
         //q->datap[0] = 1.0e38;
         q->datap[0] = MAXdata;
         break;

         case MAX:
         //q->datap[0] = -1.0e38;
         q->datap[0] = MINdata;
         break;

         default:
         error(ERR_implicit,"cannot reduce using this function");
      }
      pop();
      *sp++ = q;
      return;
   }
   q = newdat(idx.type, idx.rank, idx.size);
   copy(IN, idx.dim, q->dim, idx.rank);
   param[0] = p->datap;
   param[1] = q;
   param[2] = exop[*gsip->ptr++];
   forloop(red1, param);
   pop();
   *sp++ = q;
}

red1(param)
int param[];
{
   int i;
   data *dp, d, (*f)();

   dp = param[0];
   dp += access() + (idx.dimk-1) * idx.delk;
   f = (data (*)())param[2];
   d = *dp;
   for(i=1; i<idx.dimk; i++) {
      dp -= idx.delk;
      d = (*f)(*dp, d);
   }
   putdat(param[1], d);
}
