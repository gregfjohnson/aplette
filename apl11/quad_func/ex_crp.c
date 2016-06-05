/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"

/* quad CR - character representation
 * convert a function into a character array */

void ex_crp() {
   char name[NAMS], *iline, *c, *c2, *dp;
   struct nlist *np;
   struct item *p;
   int len, dim0, dim1, i;
   FILE   *infile;

   p = fetch1();
   if ( p->size == 0 || p->rank >1 || p->size >= NAMS ) 
      error(ERR_length, S_QUAD "cr");

   /* set up the name in search format     */
   copy(CH, (char *) p->datap, (char *) name, p->size);
   name[p->size] = '\0';
   np = nlook(name);

   /* if not found then domain error       */
   if ( !np->namep ) error(ERR_domain, S_QUAD "cr");

   switch(np->use){
   default:
      error(ERR_domain,S_QUAD "cr");
   case MF:
   case DF:
   case NF:   /* only allow functions */
      ;
   }
   infile=fdopen(wfile,"r");    /* duplicate unbuffered file wfile into
             * buffered file infile */

   /* look up function     */
   fseek( infile, (long)np->label, 0);
   
   iline = (char *) alloc(LINEMAX);
   /* alloc is a wrapper for malloc, probably takes care of
    * dynamic memory alloaction.
    */

   /* compute max width and height         */
   dim0 = 0;
   dim1 = 0;
   while ( NULL != fgets(iline,LINEMAX,infile ) ) {
      if ( strlen(iline) == 0 ) break;
      c2=iline;
      while ( *c2++ != '\n' ) ;
      dim0++;
      len = c2 - iline - 1;
      dim1 = dim1 < len ? len : dim1;
   }
   pop();      /* release old variable         */

   /* create new array and put function in */
   p = newdat ( CH, 2, dim0*dim1 );
   p->rank = 2;
   p->dim[0] = dim0;
   p->dim[1] = dim1;
   dp = (char *)(p->datap);
   fseek( infile, (long)np->label, 0);
   while ( NULL != fgets(iline,LINEMAX,infile ) ) {
      if ( strlen(iline) == 0 ) break;
      c2=c=iline;
      for ( i=0; i<dim1; i++) {
         if ( *c != '\n' ) *dp++ = *c++;
         else *dp++ = ' ';    /* fill w/blanks*/
      }
   }
   aplfree((int *) iline);

   /* put the new array on the stack       */
   *sp++ = p;

   /* reset the current file               */
   fclose(infile);
}
