/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "memory.h"
#include "utility.h"
#include "local_parser.h"
#include "data.h"
#include "y.tab.h"

extern	struct COMM comtab[];
#define lv yylval

int getnam(int ic)
{
   char name[NAMS], *cp;
   int c;
   struct nlist *np;

   c = ic;
   cp = name;
   do {
      if(cp >= &name[NAMS]) error(ERR_length,"name too long");
      *cp++ = c;
      c = *iline++;
   } while(alpha(c) || digit(c));
   *cp++ = 0;
   iline--;
                           /*   commands  */
   if(litflag == -1) {
      litflag = -2;
      for(c=0; comtab[c].ct_name; c++) {
         if(equal(name, comtab[c].ct_name)) break;
      }
      immedcmd = lv.charval = comtab[c].ct_ylval;
      return(comtab[c].ct_ytype);
   }
   for(np=nlist; np->namep; np++) {
      if(equal(np->namep, name)) {
         lv.charptr = (char *)np;
         switch(np->use) {
   
         case NF:
            if (context == lex2) sichk(np);
            return(nfun);

         case MF:
            if (context == lex2) sichk(np);
            return(mfun);

         case DF:
            if (context == lex2) sichk(np);
            return(dfun);
         }
         return(nam);
      }
   }
   /* look for an unallocated line in nlist */
   for(np=nlist; np->namep; np++) {
      if(equal(np->namep, "#"))break;
   }

   /* place the name in nlist */
   np->namep = (char *) alloc(cp-name);
   copy(CH, name, np->namep, cp-name);
   np->type = LV;
   lv.charptr = (char *)np;
   return(nam);
}

