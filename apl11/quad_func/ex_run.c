/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "char.h"

ex_run()
{
   struct item *p;
   data *dp;
   char ebuf[100];
   int i, val;

   SECURITY_CHECK;
   p = fetch1();
   if(p->type != CH ) error(ERR_domain,"");
   if(p->rank != 1) error(ERR_rank,"");
   copy(CH, p->datap, ebuf, p->size);
   ebuf[p->size] = 0;
   val = system(ebuf);
   p = newdat(DA, 0, 1);
   p->datap[0] = (data)val;
   pop();
   *sp++ = p;
}

