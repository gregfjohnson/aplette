/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

/*
 * funedit -- edit a file and read it in.
 *
 * If the arg to funedit is non-zero, it is used as a 
 * pointer to the file name to be used.  If it is zero,
 * the namep of the function is used for the file name.
 */

extern	char *bad_fn;

funedit(fname, editor)
char *fname;
{
   struct item *p;
   int f, (*a)();
   char *c, cmd[128];

   p = sp[-1];
   if(p->type != LV) error(ERR_value,"function name not found");
   sichk(p);
   if(fname == 0) fname = ((struct nlist *)p)->namep;
   c = getenv("EDITOR");
   /* if (c == 0) c = "vi"; */
   if (c == 0) 
      error(ERR,"The variable $editor has not been set");
   strcpy(cmd, c);
   strcat(cmd, " ");
   strcat(cmd, fname);
   system(cmd);

   /* Read function into workspace.  If "funread" (which calls
    * "fundef") returns 0, an error occurred in processing the
    * header (line 0).  If this happened with "editf" or "del",
    * save the bad function in the file "bad_fn".
    */

   if (funread(fname) == 0 && fname == scr_file){
      unlink(bad_fn);
      if (badfnsv(fname)) printf("function saved in %s\n", bad_fn);
   }
}

