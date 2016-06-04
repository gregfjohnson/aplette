/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"

ex_drho()
{
   struct item *p, *q, *r;
   int s, i;
   data *dp;
   char *cp;

   p = fetch2();
   q = sp[-2];
	
   /* addition of a special case 9.8.1999/tyl
    * handle spec. case where left arg is null vector
    */
   if(p->type == CH && p->size == 0 && q->size > 0) {
      r = newdat(q->type, 0, 1);
      copy(q->type,(char *)q->datap, (char *)r->datap, 1);
      goto end;
   }

   if(p->type != DA ) error(ERR_domain,"");
   if(p->rank > 1 ) error(ERR_rank,"");
   if(q->size < 0) error(ERR_length,"");

   /* Allow null vector to be reshaped if one of the
    * dimensions is null.
    */
   if (!q->size){
      dp = p->datap;
      for(i=0; i < p->size; i++) if (fix(*dp++) == 0) goto null_ok;
      error(ERR_implicit,"dimension size 0 attempted");
   }
null_ok:

   s = 1;
   dp = p->datap;
   for(i=0; i<p->size; i++){
      if (*dp < 0) error(ERR_limit,"negative dimension attempted");
      s *= fix(*dp++);
   }
   r = newdat(q->type, p->size, s);
   dp = p->datap;
   for(i=0; i<p->size; i++) r->dim[i] = fix(*dp++);
   cp = (char *)r->datap;
   while(s > 0) {
      i = s;
      if(i > q->size) i = q->size;
      cp += copy(q->type, q->datap, cp, i);
      s -= i;
   }
end:	
   pop();
   pop();
   *sp++ = r;
   return;
}
