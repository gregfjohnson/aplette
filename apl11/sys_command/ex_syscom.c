/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"
#include "work_space.h"
#include "main.h"

void ex_syscom() {
   int i, *ip, j;
   struct item *p;
   struct nlist *n;
   double f;
   char fname[64];                  /* Array for filename */
   char *cp, *vfname();

   i = *gsip->ptr++;
   switch(i) {

   default:
      error(ERR_implicit,"unrecognised system function");

   case SCRIPT:
      SECURITY_CHECK;
      if(protofile > 0) close(protofile);
      protofile = 0;
      cp = vfname(fname);
      if(equal(cp, "off")) return;
      if((protofile = open(cp, 1)) > 0){
         lseek(protofile, 0L, 2);   /* append to existing file */
         printf("[appending]\n");
      }
      else {
         /*
          * create new file
          */
         protofile = opn(cp, 0644);
         printf("[new file]\n");
      }
      writeErrorOnFailure(protofile, "\t)script on\n", 12);
      return;

   case DEBUG:
      code_trace = ~code_trace;
      return;

   case MEMORY:
      mem_dump();
      return;

   case TRACE:
      funtrace = 1;
      return;

   case UNTRACE:
      funtrace = 0;
      return;

   case WRITE:
      funwrite(0);
      return;

   case DELL:
      sp[0] = sp[-1];      /*   duplicate top of stack  */
      sp++;
      funwrite(scr_file);
      funedit(scr_file, i);
      unlink(scr_file);
      return;


   case EDIT:
      SECURITY_CHECK;
      funedit(0, i);
      return;

   case READ:
      funread(0);
      return;

   case ERASE:
      p = sp[-1];
      sp--;
      purge_name(p);
      erase((struct nlist *) p);
      if(vars_trace) vars_dump();
      return;

   case CONTIN:
      i = opn("continue", 0644);
      wssave(i);
      printf(" continue");

   case OFF:
      Exit(0);

   case VARS:
      for(n=nlist; n->namep; n++) {
         if(n->itemp && n->use == DA ) {
            if(column+8 >= pagewidth) printf("\n\t");
            printf(n->namep);
            putchar('\t');
         }
      }
      putchar('\n');
      return;

   case FNS:
      for(n=nlist; n->namep; n++) {
         if(n->use == DF || n->use == MF || n->use == NF) {
            if(column+8 >= pagewidth) printf("\n\t");
            printf(n->namep);
            putchar('\t');
         }
      }
      putchar('\n');
      return;

   case CODE:
      n = (struct nlist *)sp[-1];
      sp--;
      switch(n->use){
      default:
         error(ERR_implicit,"function name not found");
      case NF:
      case MF:
      case DF:
         if(n->itemp == 0) funcomp(n);
         ip = (int *)n->itemp;
         printf(" [p] ");	/* prologue */
         code_dump(ip[1], 0);
         for(i=1; i < *ip; i++){
            printf(" [%d] ", i);
            code_dump(ip[i+1], 0);
         }
         printf(" [e] ");	/* epilogue */
         code_dump(ip[i+1], 0);
         printf("\n");
      }
      return;

   case SICLEAR:
      while(gsip != &prime_context) {
         ex_ibr0();
      }
      longjmp(cold_restart, 0);

   case SICOM:
      tback(1);
      return;

   case CLEAR:
      clear();
      printf("clear ws\n");
      goto warp1;            /* four lines down, or so... */

   case LOAD:
      j = opn(vfname(fname), 0);
      clear();
      wsload(j);
      printf(" %s\n", fname);
      eval_qlx();            /* possible latent expr evaluation */
warp1:
      /*
       * this garbage is necessary because clear()
       * does a brk(&end), and the normal return & cleanup
       * procedures are guaranteed to fail (miserably).
       *      --jjb 1/78
       */
      sp = stack;
      longjmp(cold_restart, 0);
      //longjmp(reset_env, 0);
      //longjmp(gsip->env, 0);

   case LIB:
      listdir();
      return;

   case COPY:
      if(gsip != &prime_context) {
         error(ERR_implicit,"si damage -- type ')sic'");
      }
      wsload(opn(vfname(fname),0));
      printf(" copy %s\n", fname);
      return;

   case DROPC:
      SECURITY_CHECK;
      cp = vfname(fname);
      if(unlink(cp) == -1) printf("[can't remove %s]\n", cp);
      return;

   case SAVE:
      SECURITY_CHECK;
      j = opn(vfname(fname), 0644);
      wssave(j);
      printf(" saved %s\n", fname);
      return;

   case SHELL:
      SECURITY_CHECK;
      ex_shell();
      return;

   case LIST:
      ex_list();
      return;

   case PRWS:
      ex_prws();
      return;

   case LICENSE:
      printf("openAPL, Copyright (C) Branko Bratkovic 1998, 1999");
      printf("\n");
      printf("This program is free software; you can redistribute it");
      printf(" and/or modify\n");
      printf("it under the terms of the GNU General Public License");
      printf(" as published by\n");
      printf("the Free Software Foundation; either version 2 of");
      printf(" the License, or\n");
      printf("(at your option) any later version.\n");
      printf("\n");
      printf("This program is distributed in the hope that it will");
      printf(" be useful,\n");
      printf("but WITHOUT ANY WARRANTY; without even the implied");
      printf(" warranty of\n");
      printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
      printf(" See the\n");
      printf("GNU General Public License for more details.\n");
      printf("\n");
      printf("You should have received a copy of the GNU General");
      printf(" Public License\n");
      printf("along with this program; if not, write to the Free");
      printf(" Software\n");
      printf("Foundation, Inc., 59 Temple Place, Suite 330, Boston,");
      printf(" MA  02111-1307  USA\n");
      return;
   }
}

char *
vfname(array)
char *array;
{
   struct nlist *n;
   char *p;

   n = (struct nlist *)sp[-1];
   sp--;
   if(n->type != LV) error(ERR_value,"not a local varaible");
   p = n->namep;
   while(*array++ = *p++);
   return(n->namep);

}

