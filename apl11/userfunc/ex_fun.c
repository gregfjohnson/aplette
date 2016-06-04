/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

int prolgerr;      /* Flag -- set if bad fetch in prologue 
                    * this variable is global so that fetch()
                    * is able to set it */

ex_fun()
{
   struct nlist *np;
   int *p, s;
   struct Context *thisContext;

   gsip->ptr += copy(IN, gsip->ptr, &np, 1);
   
   //gsip->oldpcp=pcp;

   if(np->itemp == 0) funcomp(np);
   p = (int *)np->itemp;

   thisContext=(struct Context *)alloc(sizeof(struct Context));
   thisContext->prev = gsip;            /* setup new state indicator */
   thisContext->Mode = deffun;
   thisContext->np = np;
   //thisContext->oldsp = 0;   /* we can add a more complicated version, later */
   thisContext->sp = sp;    /* we can add a more complicated version, later */
   //thisContext->oldpcp = pcp;
   thisContext->funlc = 0;
   thisContext->suspended = 0;
   gsip = thisContext;

   prolgerr = 0;            /* Reset error flag */
   s = p[0];
   checksp();
   if(funtrace) printf("\ntrace: fn %s entered: ", np->namep);
   if (setjmp(gsip->env)) goto reenter;
   while(1){
      gsip->funlc++;
      if(funtrace) printf("\ntrace: fn %s[%d]: ", np->namep, gsip->funlc-1);
      //execute_old(p[si->funlc]);
      gsip->pcode=p[gsip->funlc];
      gsip->ptr=gsip->pcode;
      execute();
      if(gsip->funlc == 1){
         gsip->sp = sp;
         if (prolgerr) error(ERR_botch,"prolog problem");
      }
      if(intflg) error(ERR_interrupt,"");

   reenter:
      if(gsip->funlc <= 0 || gsip->funlc >= s) {
         gsip->funlc = 1;      /* for pretty traceback */
         if(funtrace) printf("\ntrace: fn %s exits ", np->namep);
         //execute_old(p[s+1]);
         gsip->pcode=p[s+1];
         gsip->ptr=gsip->pcode;
         execute();

         gsip = gsip->prev;      /* restore state indicator to previous state */
         //pcp = gsip->oldpcp;
	 aplfree(thisContext);
         return;
      }
      pop();
   }
}

