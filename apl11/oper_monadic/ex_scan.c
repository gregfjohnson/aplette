/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "opt_codes.h"

ex_scn0()
{
   fetch1();
   scan0(0);
}

ex_scan()
{
   struct item *p;

   p = fetch1();
   scan0(p->rank-1);
}

ex_scnk()
{
   int i;

   i = topfix() - iorigin;
   scan0(i);
}

scan0(k)
{
   struct item *p, *q;
   data *param[2];
   int scan1();

   p = fetch1();
   if(p->type != DA) error(ERR_domain,"not numeric data");
   bidx(p);
   colapse(k);
   if(idx.dimk == 0) {
/*
 *  scan identities - ets/jrl 5/76
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
         q->datap[0] = 1.0e38;
         break;
   case MAX:
         q->datap[0] = -1.0e38;
         break;
   default:
         error(ERR_implicit,"cannot scan with this function");
      }
      pop();
      *sp++ = q;
      return;
   }
   param[0] = p->datap;
   param[1] = (data *)exop[*gsip->ptr++];
   forloop(scan1, param);
}

scan1(param)
data *param[];
{
   int i, j;
   data *dp, *ip, d, (*f)();

   f = (data (*)())param[1];
   for (i=0; i<idx.dimk; i++) {
      dp = param[0] + access() + (idx.dimk - (i+1)) * idx.delk;
      ip = dp;
      d  = *ip;
      for (j=1; j<idx.dimk-i; j++) {
         ip -= idx.delk;
         d = (*f)(*ip, d);
      }
      *dp = d;
   }
}
