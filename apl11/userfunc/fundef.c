/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "memory.h"
#include "work_space.h"
#include "userfunc.h"
#include "parser.h"
#include "main.h"

/*
 * fundef - defines a function
 * Once a file has been edited by the user, this routine
 * will read into the workspace file.  It will also attempt
 * a compile of just the header and return an error if
 * the parser cannot use it.
 *
 * It uses a mix of buffered and nonbuf IO.
 */
 
int fundef(int f) {
   int a;
   char *iline, *status, *c;
   SymTabEntry *np;
   char b[512];
   FILE *infile;

   // duplicate unbuffered file f into buffered file infile
   infile=fdopen(f,"r");

   iline= (char *) alloc(LINEMAX);

   status=fgets(iline,LINEMAX,infile);
   if (ascii_characters) {
        char *oldline = (char *) alloc(LINEMAX);
        iline[strlen(iline)-1] = '\0';
        strncpy(oldline, iline, LINEMAX);
        iline = to_ascii_input(oldline);
        aplfree((int *) oldline);
   }

   if (status == NULL || 0 == strcmp(iline, "\n") ) { 
      printf("Blank function header. \n");
      aplfree((int *) iline);
      return(0);
   }

   c = compile_old(iline, 2);
   aplfree((int *) iline);
   if (c == 0) goto out;
   copy(PTR, (char *) c+1, (char *) &np, 1);
   sichk(np);
   erase(np);
   np->use = ((struct chrstrct *)c)->c[0];
   aplfree((int *) c);

   // save current length of file..
   np->label = lseek(wfile, 0L, 2);

   fseek(infile, 0L, 0); /* set file pointer to BOF */

   // copy infile to wfile..
   while((a=fread(b, 1, 512, infile)) > 0) writeErrorOnFailure(wfile, b, a);
   writeErrorOnFailure(wfile, "", 1);

out:
   fclose(infile);
   return(1);
}
