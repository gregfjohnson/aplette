/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void ex_nc() {
   struct nlist *np;
   struct item *p;
   int i;
   char buf[40];

   p = fetch1();
   if(p->type != CH) error(ERR_domain,"");
   if(p->size >= 40 || p->rank > 1) error(ERR_rank,"");
   copy(CH, (char *) p->datap, (char *) buf, p->size);
   buf[p->size] = 0;
   np = nlook(buf);
   i = 0;
   if(np != 0) {
      switch(np->use){
      case 0:
         i = 0; break;
      case MF:
      case NF:
      case DF:
         i = 3; break;
      case DA:
      case CH:
      case LV:
         i = 2; break;
      default:
         printf("unknown ",S_QUAD,"nc type = %d\n", np->use);
         i = 4;
      }
   }
   p = newdat(DA, 0, 1);
   p->datap[0] = i;
   pop();
   *sp++ = p;
}
