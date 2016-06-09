/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "utility.h"
#include "local_parser.h"
#include "y.tab.h"
#include "opt_codes.h"
#include "memory.h"

/*
 * s is statement
 * f is execution flag:
 *   0 compile immediate
 *   1 compile quad input
 *   2 function definition
 *   3 function prolog
 *   4 function epilog
 *   5 function body
 */
extern int     ilex[];

char *compile_old(char *s, int f) {
   char *p, *q;

   iline = s;
   ccharp = oline;
   litflag = 0;
   nlexsym = ilex[f];
   context = nlexsym;
   if(yyparse()) {
      pline(s, iline-s, lineNumber);	//print line and error pointer
      return(0);
   }
   *ccharp++ = END;
   iline = p = (char *) alloc(ccharp-oline);
   for(q=oline; q<ccharp;) *p++ = *q++;
   return(iline);
}

