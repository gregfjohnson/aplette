/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "execute.h"

/* this routine deals with dyadic scalar functions
 * where both arguments are type char
 * it adjusts the shape of the arguments as required
 */
 
void ex_cdyad(data (*f)(), struct item *ap, struct item **ap1) {
   int i;
   struct item *p, *p1;
   char *cp;
   data d1, d2;

   p = ap;
   p1 = ap1;
   if(p->rank == 0 || p->size == 1) {
      d1 = ((struct chrstrct *)p->datap)->c[0];
      pop();
      p = p1;
      cp = (char *)p->datap;
      for(i=0; i<p->size; i++) {
         d2 = *cp;
         *cp = (*f)(d1, d2);
         cp++;
      }
   }
   else if(p1->rank == 0 || p1->size == 1) {
      sp--;
      d1 = ((struct chrstrct *)p1->datap)->c[0];
      pop();
      *sp++ = p;
      cp = (char *)p->datap;
      for(i=0; i<p->size; i++) {
         d2 = *cp;
         *cp = (*f)(d2, d1);
         cp++;
      }
   }
   else {
      if(p1->rank != p->rank) error(ERR_rank,"cdyad - arrays do not match");
      for(i=0; i<p->rank; i++) {
         if(p->dim[i] != p1->dim[i]) 
            error(ERR_length,"cdyad - dimensions do not match");
      }
      cp = (char *)p1->datap;
      for(i=0; i<p->size; i++) {
         d1 = ((struct chrstrct *)p->datap)->c[i];
         d2 = *cp;
         *cp = (*f)(d1, d2);
         cp++;
      }
      p = p1;
      pop();
   }
   /*
    * now convert the character vector to
    * a numeric array.  Someday, we can make this a
    * call to whomever creates "logical" type data.
    */
   p1 = p;
   cp = (char *)p->datap;
   p = newdat(DA, p->rank, p->size);
   for(i=0; i<p->rank; i++) p->dim[i] = p1->dim[i];
   for(i=0; i<p->size; i++) p->datap[i] = (*cp++) & 0377;
   pop();
   *sp++ = p;
}
