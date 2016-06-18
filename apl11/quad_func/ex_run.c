/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void ex_run() {
   struct item *p;
   char ebuf[100];
   int val;

   SECURITY_CHECK;
   p = fetch1();
   if(p->type != CH ) error(ERR_domain,"");
   if(p->rank != 1) error(ERR_rank,"");
   copy(CH, (char *) p->datap, (char *) ebuf, p->size);
   ebuf[p->size] = 0;
   val = system(ebuf);
   p = newdat(DA, 0, 1);
   p->datap[0] = (data)val;
   pop();
   *sp++ = p;
}
