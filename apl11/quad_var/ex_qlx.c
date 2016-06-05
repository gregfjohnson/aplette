/* openAPL, Copyright (C) Branko Bratkovic 1998
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */

#include <stdio.h>
#include "apl.h"
#include "data.h"
#include "char.h"
#include "memory.h"

struct item * ex_qlx(io)
int io; /* 0 = source, 1 = sink */
{
struct item *p, *q;
struct nlist *n;

   if ( io == 0 ) { 
      n = nlook(S_QUAD "lx");
      if(n){
         q = n->itemp;
         p = dupdat(q);
         copy(q->type, (char *) q->datap, (char *) p->datap, q->size);
      }
      else p = newdat(CH, 1, 0);
      return(p);
   } else {

      pop();
      n = nlook(S_QUAD "lx");
      if(n == 0){ /* allocate new name: */
         for(n=nlist; n->namep; n++) ;
         n->namep = (char *)alloc(4);
         copy(CH, (char *) S_QUAD "lx", (char *) n->namep, 4);
         n->type = LV;
         n->use = 0;
         n->itemp = newdat(CH, 0, 0);
      }
      q = fetch1();
      erase(n);
      n->use = DA;
      ((struct nlist *)n)->itemp = q;
      sp[-1] = (struct item *)n;

      return(0);
   };
}
