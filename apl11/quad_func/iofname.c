/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
   static char b[200];

char *iofname(m)
{
   struct item *p;

   p = fetch1();
   if(p->type != CH || p->rank > 1) error(ERR_implicit,"file name");
   copy(CH, p->datap, b, p->size);
   b[p->size] = 0;
   pop();
   return(b);
}

