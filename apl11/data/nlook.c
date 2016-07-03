/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

SymTabEntry *
nlook(name)
char *name;
{
   SymTabEntry *np;

   for(np = symbolTable; np->namep; np++) {
      if(equal(np->namep, name)) return(np);
   }
   return(0);
}

