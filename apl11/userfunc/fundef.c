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
#include "utility.h"

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

   status = readLine("fundef verify first line", iline, LINEMAX, infile);

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


   // the scheme is, we write function definitions into our
   // workspace temporary file.  The workspace temporary
   // file can have multiple function definitions written into it,
   // none of which have been actually compiled.
   //
   // we lazily compile, and only get around to compiling a function
   // that has been read in the first time it actually gets used.
   //
   // this may have to do with the possibility that names changed
   // what they were bound to.  so maybe we want to re-compile
   // every time just prior to executing.
   //
   // we save the location in the workspace temporary file where
   // we are about to write the current function being defined.
   // after writing that function, we write a blank line out to the
   // workspace temporary file.  that appears to be the way we
   // delineate file definitions that have all been saved up, and the
   // signal to the compiler that we are done compiling a particular
   // function definition.
   //

   np->label = lseek(wfile, 0L, 2);

   fseek(infile, 0L, 0);

   // copy infile to wfile..
   while((a=fread(b, 1, 512, infile)) > 0) {
      writeErrorOnFailure(wfile, b, a);
   }
   writeErrorOnFailure(wfile, "", 1);

out:
   fclose(infile);
   return(1);
}
