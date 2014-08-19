/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "parser.h"
/*   Byte-order dependency here?  */
/*   Potential alignment problem here?  */
char * name(np, c)
{
   char *p, *npp;
   int temp;

   temp = np;
   npp = (char *)&temp;
   p = ccharp;
   *ccharp++ = c;
   *ccharp++ = *npp++;
   *ccharp++ = *npp++;
   *ccharp++ = *npp++;
   *ccharp++ = *npp++;
   return(p);
}

