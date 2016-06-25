/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "work_space.h"

/* creates an ordinary file from a user defined function
 * in order to enable the user to edit it through a subsequent
 * call to a text editor
 */
void funwrite(char *fname) {
   SymTabEntry *n;
   int i, cnt, fd1, fd2;
   char buf[512];

   n = (SymTabEntry *)sp[-1];
   sp--;
   if(n->type != LV) error(ERR_botch,"fnwrite");
   if(fname ==0) fname = n->namep;
   fd1 = opn(fname, 0644);
   /* opn() defined elsewhere is a wrapper for open() 
    * it returns a file descriptor, used for nonbuffered IO
    */
   switch(n->use){
   default:
      close(fd1);
      error(ERR,"fnwrite");

   /*   Undefined function -- print that and do nothing  */
/*   case 0:
      printf("\t[new fn]\n");
      break; */

   /* First time function declaration */
   case 0:
      printf("\t[new fn]\n");
      /* We can get away with the following because struct current_line
       * was made global and function editing is only permitted
       * from the keyboard.  If this subroutine were called from
       * []lx or downtack-jot, the input line would not be
       * current_line and the following would break.
       */
      writeErrorOnFailure(fd1, gsip->text,strlen(gsip->text));
   break;


   /*   Function already defined  */
   case NF:
   case MF:
   case DF:
      fd2 = dup(wfile);
      lseek(fd2, (long)n->label, 0);
      do {
         cnt = read(fd2, buf, 512);
         if(cnt <= 0) error(ERR,"fnwrite eof");
         for(i=0; i<cnt; i++) if(buf[i] == 0) break;
         writeErrorOnFailure(fd1, buf, i);
      } while(i == 512);
      close(fd2);
   break;
   }
   close(fd1);
}

