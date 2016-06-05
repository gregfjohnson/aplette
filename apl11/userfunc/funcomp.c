/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "memory.h"

/*
 * funcomp - compile functions
 * during run time, a user defined function is invoked and
 * compiled before being executed.
 *
 * It uses a mix of buffered and nonbuf IO.
 *
 */

char *labcpp,*labcpe;
extern char *catcode();

void funcomp(struct nlist *np) {
   char labp[MAXLAB*20], labe[MAXLAB*4];
   char  *a, *c; 
   int  i, err, err_code, *p;
   char	*iline, *status, *phase, *err_msg;
   struct Context *original_gsip, *FunctionLine, 
                  *Prologue, *Epilogue;
   FILE *infile;

   /* as gsip is used during compilation, we have to save the original
    * and restore it upon exit
    */
   original_gsip=gsip;	
   err_code=0; err_msg="";
   infile = fdopen(wfile,"r");
   err=fseek(infile, (long)np->label, 0);
   if ( err != 0 ) error(ERR_implicit,"Could not find function in workspace");
   err = 0;
   lineNumber = 0;
   iline=(char *)alloc(LINEMAX);

  /* Phase 1 creates the first of a linked list of compiled
   * function lines.  This first line will contain the prologue
   */
   //printf("Phase 1 \n");
   phase="Phase 1";
   Prologue=(struct Context *)alloc(sizeof(struct Context));
   Prologue->Mode=deffun;
   Prologue->suspended=0;
   Prologue->prev=0;
   Prologue->text=(char *)NULL;
   Prologue->pcode=(char *)NULL;
   //Prologue->xref=(char *)NULL;
   Prologue->sp=0;

   /* get the first line */
   status=fgets(iline,LINEMAX,infile);
   if ( 0 == strlen(iline) || status == NULL) {
      err_code=ERR_implicit;
      err_msg="empty header line";
      goto out;
   }
   Prologue->text=iline;
   gsip=Prologue;
   labgen = 0;
   compile_new(3);	/* 3 = compile function prologue */
   if(gsip->pcode == 0) {
      err_code=ERR_implicit;
      err_msg="invalid header line";
      goto out;
   }

  /* Phase 2 compiles the body of the function */
   //printf("Phase 2 \n");
   phase="Phase 2";
   labcpp = labp;
   labcpe = labe;
   labgen = 1;

   while (1) {
      status=fgets(iline,LINEMAX,infile);
   if ( 0 == strlen(iline) || status == NULL) break;
      /* create a new Context */
      FunctionLine=(struct Context *)alloc(sizeof(struct Context));
      FunctionLine->Mode=deffun;
      FunctionLine->suspended=0;
      FunctionLine->prev=gsip;	/* link to previous */
      FunctionLine->text=(char *)NULL;
      FunctionLine->pcode=(char *)NULL;
      //FunctionLine->xref=(char *)NULL;
      FunctionLine->sp=0;
      FunctionLine->text=iline;

      gsip=FunctionLine;
      lineNumber++;
      compile_new(5);	/* 5 = compile function body */
      if ( MAXLAB <= (labcpe-labe)/5+1) {
         err_code=ERR_botch;
         err_msg="too many labels, edit MAXLAB in apl.h and recompile";
#include "utility.h"
         goto out;
      }
      if(gsip->pcode == 0) {
         err++;
      } 
   }
   if ( err ) {
      err_code=ERR_implicit;
      err_msg="compilation errors";
      goto out;
   }
   /* At the end of this Phase, lineNumber=Maximum_No_of_lines
    * but we want to include the Prologue (line 0) and 
    * Epilogue (so add one to lineNumber)
    */
    lineNumber++;

   /* development aid.... * /
   printf("At end of Phase 2...\n");
   for (i=lineNumber; i>1; i-- ) {
      printf("[%d] ",i-1);
      code_dump(FunctionLine->pcode,0);
      FunctionLine=FunctionLine->prev;
   }
   printf("[p] "); code_dump(Prologue->pcode,0);
   printf("[0] %d\n",lineNumber);
   /**/
   
   /* Phase 3 - dealing with labels */
   phase="Phase 3a";
   /* generate the Epilogue */
   fseek(infile, (long)np->label, 0);
   status=fgets(iline,LINEMAX,infile);
   if ( 0 == strlen(iline) ) {
      err++;
      err_code=ERR_implicit;
      goto out;
   }
   Epilogue=(struct Context *)alloc(sizeof(struct Context));
   Epilogue->Mode=deffun;
   Epilogue->suspended=0;
   Epilogue->prev=gsip;
   Epilogue->text=iline;
   Epilogue->pcode=(char *)NULL;
   //Epilogue->xref=(char *)NULL;
   Epilogue->sp=0;
   labgen = 0;
   gsip=Epilogue;
   compile_new(4);	/* 4 = compile function epilogue */
   if(gsip->pcode == 0) {
      err_code=ERR_implicit;
      err_msg="invalid header line";
      goto out;
   }

   /* only conduct phase 3b/c if labels were generated */
   if(labcpp != labp){
      phase="Phase 3b";
      /* append the label-epilogue to the Epilogue */
      reverse(labe);
      c=Epilogue->pcode;
      Epilogue->pcode = catcode(labe, c);
      aplfree((int *) c);

      phase="Phase 3c";
      /* At this point, we have:
       * fn-prologue (p[1]):      <AUTOs and ARGs>, ELID, END
       * label-prologue (labp):   <AUTOs and LABELs>, END
       * 
       * and we want to produce:
       * fn-prologue (p[1]):   <AUTOs and ARGs>,<AUTOs and LABELs>,  ELID, END.
       */
      a = csize(Prologue->pcode) - 1;
      c = csize(labp) - 1;

      /* Move the ELID from the end of the fn-prologue,
       * to the end of the label-prologue.
       */
      if (((struct chrstrct *)Prologue->pcode)->c[(int)a-1] == ELID) {
         ((struct chrstrct *)Prologue->pcode)->c[(int)a-1] = END;
         labp[(int)c] = ELID;
         labp[(int)c+1] = END;
      } else {
         err_code=ERR_botch;
         err_msg="elid";
         goto out;
      }

      /* Append the label-prologue to the Prologue */
      a = Prologue->pcode;
      Prologue->pcode = catcode(a,labp);
      aplfree((int *) a);
   }

   if(code_trace) {
      code_dump(Prologue->pcode, 1);	/* show the prologue */
      code_dump(Epilogue->pcode, 1);	/* show the epilogue */
   }

  /* Phase 4 goes through the compiled lines
   * storing pointers to each pcode in p[]
   */
   //printf("Phase 2a \n");
   phase="Phase 4";
   p = (int *)alloc((lineNumber+2)*SINT);
   FunctionLine=Epilogue;
   for (i=lineNumber+1; i>0; i-- ) {
      p[i] = FunctionLine->pcode;
      FunctionLine=FunctionLine->prev;
   }
   p[0] = lineNumber;

   /* development aid.... * /
   printf("At end of Phase 4...\n");
   printf("[0] %d\n",p[0]);
   printf("[p] "); code_dump(p[1],0);
   for (i=2; i<=lineNumber; i++ ) {
      printf("[%d] ",i-1);
      code_dump(p[i],0);
   }
   /**/

   /* put the result into effect */
   np->itemp = (struct item *)p;
   err = 0;

out:
//printf("Phase out \n");
   fclose(infile);
   aplfree((int *) iline);
   gsip=original_gsip;	
   if (err_code) {
      if (np->namep) printf("%s in function %s\n", phase, np->namep);
      error(err_code,err_msg);
   }
}

