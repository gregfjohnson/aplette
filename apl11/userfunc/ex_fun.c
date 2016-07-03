/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"
#include "userfunc.h"
#include "execute.h"

int prolgerr;      /* Flag -- set if bad fetch in prologue 
                    * this variable is global so that fetch()
                    * is able to set it */

void ex_fun() {
   SymTabEntry *np;
   int functionLineCount;
   int functionPcodeLineLength;
   char **pcodeLineArray;
   struct Context *thisContext;

   gsip->ptr += copy(PTR, (char *) gsip->ptr, (char *) &np, 1);
   
   if(np->functionPcodeLines == NULL) funcomp(np);
   pcodeLineArray = np->functionPcodeLines;

   thisContext=(struct Context *)alloc(sizeof(struct Context));
   thisContext->prev = gsip;            /* setup new state indicator */
   thisContext->Mode = deffun;
   thisContext->np = np;
   thisContext->sp = sp;    /* we can add a more complicated version, later */
   thisContext->funlc = 0;
   thisContext->suspended = 0;
   gsip = thisContext;

   prolgerr = 0;            /* Reset error flag */

   functionLineCount       = np->functionLineCount;
   functionPcodeLineLength = np->functionPcodeLineLength;

   checksp();
   if(funtrace) printf("\ntrace: fn %s entered:\n", np->namep);
   if (setjmp(gsip->env)) goto reenter;
   while(1){
      gsip->funlc++;
      if(funtrace) printf("\ntrace: fn %s[%d]:\n", np->namep, gsip->funlc-1);
      gsip->pcode = pcodeLineArray[gsip->funlc-1];
      gsip->ptr = gsip->pcode;
      execute();
      if(gsip->funlc == 1){
         gsip->sp = sp;
         if (prolgerr) error(ERR_botch,"prolog problem");
      }
      if(intflg) error(ERR_interrupt,"");

   reenter:
      if(gsip->funlc < 0 || gsip->funlc >= functionLineCount) {
         gsip->funlc = 1;      /* for pretty traceback */

         if(funtrace) printf("\ntrace: fn %s exits\n", np->namep);

         gsip->pcode = pcodeLineArray[functionPcodeLineLength-1];
         gsip->ptr = gsip->pcode;
         execute();

         gsip = gsip->prev;      /* restore state indicator to previous state */
         //pcp = gsip->oldpcp;
	     aplfree((int *) thisContext);
         return;
      }
      pop();
   }
}
