/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

/*
 * produce trace back info
 */

char *atfrom[] = {"at\t", "from\t", "", ""};

tback(flag)
{
struct Context *thisContext;
int i;

   if ( gsip == &prime_context ) 
      return;	/* don't attempt to trace state zero */
   else thisContext=gsip ;
   i = 0;
   if(flag) i = 2;
   while(thisContext != &prime_context) {
      if (thisContext->Mode == deffun) {
         if(flag==0 && thisContext->suspended) return;
         if (thisContext->funlc != 1 || i){   /* skip if at line 0 */
            printf("%s%s[%d]%s\n",
               atfrom[i],
               thisContext->np->namep,
               thisContext->funlc - 1,
               (thisContext->suspended ? "   *" : "")
            );
            i |= 1;
         }
      }
      thisContext = thisContext->prev;
   }
}

