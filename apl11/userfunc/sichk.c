/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

void sichk(struct nlist *n) {
   struct Context *p;

   p = gsip;
   while(p){
      if(n == p->np) error(ERR,"si damage -- type ')sic'");
      p = p->prev;
   }
}
