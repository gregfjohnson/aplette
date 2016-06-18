/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "apl.h"
#include "utility.h"

/* List a function on the terminal */
void ex_list() {
   char lastc, c;
   struct nlist *n;
   int line;

   /* Check for valid function */

   n = (struct nlist *)*--sp;
   if (n->type != LV) error(ERR_value,"function name not defined");

   /* If a function, locate it in workspace file and
    * print on the terminal in formatted form.
    */

   switch(((struct nlist *)n)->use){
   default:
      error(ERR_botch,"cannot find requested function");

   case NF:
   case MF:
   case DF:
      lseek(wfile, (long)n->label, 0);
      line = 0;
      lastc = 0;
      putchar('\n');

      while(read(wfile, &c, 1) > 0){

         if (!c){
            putchar('\n');
            return;
         }

         switch(lastc){
         case '\n':
            printf("[%d]", ++line);
         case 0:
            putchar('\t');
         }
         putchar(lastc=c);
      }
      error(ERR_botch,"unexpected EOF");
   }
}

