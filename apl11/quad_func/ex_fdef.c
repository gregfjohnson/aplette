/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "work_space.h"

void ex_fdef() {
   struct item *p;
   char *p1, *p2;
   struct nlist *np;
   char b[512];
   int i, dim0, dim1;

   p = fetch1();
   if( p->rank != 2 && p->rank != 1 ) error(ERR_rank,"");
   if(p->type != CH) error(ERR_domain,"");

   /* The following code has been commented out as a
    * test of slight modifications to the compiler.
    * Before this change, it was impossible to use quad-FX
    * from inside an APL function, for it might damage
    * an existing function by the same name.  The compiler
    * now checks when processing function headers to see
    * if the function is suspended by calling "sichk", which
    * will generate an error if so.  Hopefully this will now
    * allow quad-FX to be used freely without disastrous side-
    * effects.
    *
   if(gsip) error(ERR,"si damage -- type ')sic'");
    */

   dim0 = p->dim[0];
   dim1 = p->dim[1];
   if(p->rank == 1) dim1 = dim0;
   copy(CH, (char *) p->datap, (char *) b, dim1);
   b[dim1] = '\n';

   p2 = compile_old(b, 2);
   if(p2 != 0){
      copy(IN, (char *) p2+1, (char *) &np, 1);
      erase(np);
      np->use = *p2;
      aplfree((int *) p2);
   
      np->label = lseek(wfile, 0L, 2);
      fappend(wfile, p);
      writeErrorOnFailure(wfile,"",1);
   }
   pop();
   *sp++ = newdat(DA, 1, 0);
}
