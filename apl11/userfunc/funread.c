/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

void funread(char *fname) {
   struct item *p;
   int f, pid;

   p = sp[-1];
   sp--;
   if(p->type != LV) error(ERR_value,"not a local varaible");
   if(fname == 0) fname = ((struct nlist *)p)->namep;
   f = opn(fname, 0);
   return(fundef(f));
}
