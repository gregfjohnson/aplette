/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "char.h"

/*
 * monadic immediate branch -- resume fn at specific line
 */

ex_ibr()
{
struct Context *thisContext;

   if( gsip == &prime_context || gsip->prev->suspended == 0) {
      error(ERR_implicit,"no suspended fn");
   }

   /* throw away current context */
   thisContext=gsip;
   gsip=gsip->prev;
   aplfree(thisContext);

   ex_br();
   if(gsip->sp == 0 || sp < gsip->sp) 
      error(ERR_botch,"stack pointer problem");
   while(sp > gsip->sp) pop();
   longjmp(gsip->env, 0);         /* warp out */
}

