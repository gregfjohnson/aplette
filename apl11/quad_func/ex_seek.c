/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"
#include "char.h"

ex_seek()
{
   struct item *p;
   int k1, k3;
   long k2;

   SECURITY_CHECK;
   p = fetch1();
   if(p->type != DA ) error(ERR_domain,"");
   if(p->rank != 1 ) error(ERR_rank,"");
   if(p->size != 3) error(ERR_length,"");
   k1 = p->datap[0];
   k2 = p->datap[1];
   k3 = p->datap[2];
   k1 = lseek(k1, k2, k3);
   pop();
   iodone(k1);
}

