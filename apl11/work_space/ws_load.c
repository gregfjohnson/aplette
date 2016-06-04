/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
/* #include <string.h>
#include <dirent.h> */
#include <stdlib.h>	/* atof() */

wsload(ffile)
{
   char buffer[64], flag, *gettoken(), c;
   int use, size, rank, i, dim[MRANK];
   struct nlist *n;
   struct item *p;

   gettoken(ffile, buffer);
   if (!equal(buffer, "apl\\11")) error(ERR,"bad ws file magic number");
   gettoken(ffile, buffer);
   gettoken(ffile, buffer);
   tolerance = atof(buffer);
   gettoken(ffile, buffer);
   gettoken(ffile, buffer);
   iorigin = atoi(buffer);
   gettoken(ffile, buffer);
   gettoken(ffile, buffer);
   pagewidth = atoi(buffer);
   gettoken(ffile, buffer);
   gettoken(ffile, buffer);
   PrintP = atoi(buffer);

   while (1) {
      if (0 == gettoken(ffile, buffer)) break;
      if (equal(buffer, "DA")) use = DA;
      if (equal(buffer, "CH")) use = CH;
      if (equal(buffer, "NF")) use = NF;
      if (equal(buffer, "MF")) use = MF;
      if (equal(buffer, "DF")) use = DF;

      gettoken(ffile, buffer);
      for (n=nlist; n->namep; n++) {
         if (equal(buffer, n->namep)) {
            erase(n);
            goto hokay;
         }
      }
      n->namep = alloc(1+strlen(buffer));
      strcpy(n->namep, buffer);
hokay:
      n->use = use;
      if (n->use == CH) n->use = DA;
      n->type = LV;

      switch (use) {

         default:
         close(ffile);
         error(ERR,"bad ws file format");

         case DA:
         case CH:
         rank = atoi(gettoken(ffile, buffer));
         size = 1;
         for (i=0; i<rank; i++) {
            dim[i] = atoi(gettoken(ffile, buffer));
            size *= dim[i];
         }
         p = newdat(use, rank, size);
         for (i=0; i<rank; i++) p->dim[i] = dim[i];
         if (use == CH) read(ffile, (char *)p->datap, size);
         else {
            read(ffile, (data *)p->datap, size*sizeof(data));
         }
         n->itemp = p;
         break;

         case NF:
         case MF:
         case DF:
         n->itemp = 0;
         n->label = lseek(wfile, 0L, 2);
         while (1) {
            if (read(ffile, &c, 1) != 1) {
               close(ffile);
               error(ERR,"wsload unexpected eof");
            }
            write(wfile, &c, 1);
            if (c == 0) break;
         }
         break;
      }
   }

   fdat(ffile);
   close(ffile);
}


/* static - this declaration produced a warning */
char *
gettoken(ffile, buffer)
char *buffer;
{
   int i;
   char c;

   i = 0;
   while (1) {
      if (read(ffile, &c, 1) != 1) return 0;
      if (isspace(c)) continue;
      break;
   }
   buffer[i++] = c;
   while (1) {
      if (read(ffile, &c, 1) != 1) break;
      if (isspace(c)) break;
      buffer[i++] = c;
   }
   buffer[i] = 0;
   return buffer;
}

