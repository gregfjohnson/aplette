/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
#include "utility.h"

/* this routine deals with dyadic scalar functions
 * where both of the arguments are floating point (ie double)
 * it adjusts the shape of the arguments as required
 */

void ex_ddyad(data (*f)(), struct item *ap, struct item *ap1) {
   int i;
   struct item *p;
   struct item *p1;
   data *dp, d;

   /* Conform arguments to function if necessary.  If they
    * do not conform and one argument is a scalar, extend
    * it into an array with the same dimensions as the
    * other argument.  If neither argument is a scalar, but
    * one is a 1-element vector, extend its shape to match
    * the other argument.
    */

   p = ap;
   p1 = ap1;

   if(p->rank < 2 && p->size == 1 && p1->rank != 0){
      d = p->datap[0];
      pop();
      p = p1;
      dp = p->datap;
      for(i=0; i<p->size; i++) {
         *dp = (*f)(d, *dp);
         dp++;
      }
      return;
   }
   if(p1->rank < 2 && p1->size == 1) {
      sp--;
      d = p1->datap[0];
      pop();
      *sp++ = p;
      dp = p->datap;
      for(i=0; i<p->size; i++) {
         *dp = (*f)(*dp, d);
         dp++;
      }
      return;
   }
   if(p1->rank != p->rank) error(ERR_rank,"ddyad - ranks do not match");
   for(i=0; i<p->rank; i++) {
      if(p->dim[i] != p1->dim[i]) 
         error(ERR_length,"ddyad - dimensions do not match");
   }
   dp = p1->datap;
   for(i=0; i<p->size; i++) {
      *dp = (*f)(p->datap[i], *dp);
      dp++;
   }
   pop();
}
