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
#include "char.h"

struct item * ex_quad(io)
int io; /* 0 = source, 1 = sink */
{
char *getinput();
struct item *p;
struct Context *thisContext;

   if ( io == 0 ) { 
      thisContext=(struct Context *)alloc(sizeof(struct Context));
      thisContext->prev = gsip;            /* setup new context */
      thisContext->Mode = deffun;
      //thisContext->np = np;
      thisContext->sp = 0;
      //thisContext->ptr = thisContext->pcode;
      //thisContext->funlc = 0;
      //thisContext->suspended = 0;
      
      gsip = thisContext;
      do {
         gsip->text=getinput(S_QUAD ":\t");
         if(!isatty(0)) printf("%s",gsip->text);
         if(gsip->text == NULL) error(ERR,"user input was null");
         compile_new(1);
      } while ( gsip->pcode == 0 ); /* do it at least once */
      //i = pcp;
      gsip->ptr=gsip->pcode;
      execute();
      //pcp = i;
      p = *--sp;
      gsip=thisContext->prev;      /* restore previous context */
      aplfree(thisContext->text);
      aplfree(thisContext->pcode);
      aplfree(thisContext);
      //pcp = context->oldpcp;
      return(p);
   } else {
      pop();
      ex_print();
      return(0);
   };
}
