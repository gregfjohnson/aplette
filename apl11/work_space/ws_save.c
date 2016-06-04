/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

wssave(ffile)
{
   struct nlist *n;

   nsave(ffile, 0);
   for(n=nlist; n->namep; n++) nsave(ffile, n);
   fdat(ffile);
   close(ffile);
}

nsave(ffile, an)
struct nlist *an;
{
   char c, buffer[64];
   int i, n, size;
   struct item *p;

   if (an == 0){
      write(ffile, "apl\\11\n", 7);
      sprintf(buffer, "tolerance %lg\n", tolerance);
      write(ffile, buffer, strlen(buffer));
      sprintf(buffer, "origin %d\n", iorigin);
      write(ffile, buffer, strlen(buffer));
      sprintf(buffer, "width %d\n", pagewidth);
      write(ffile, buffer, strlen(buffer));
      sprintf(buffer, "digits %d\n", PrintP);
      write(ffile, buffer, strlen(buffer));
      return 0;
   }

   if (an->use == 0 || (an->use == DA && an->itemp == 0)) return 0;

   switch (an->use) {
      default:
      close(ffile);
      error(ERR_botch,"type is unknown");

      case DA:
      p = an->itemp;
      if (p->type == DA) write(ffile, "DA ", 3);
      else write(ffile, "CH ", 3);
      write(ffile, an->namep, strlen(an->namep));
      sprintf(buffer, " %d", p->rank);
      write(ffile, buffer, strlen(buffer));
      size = 1;
      for (i=0; i<p->rank; i++) {
         sprintf(buffer, " %d", p->dim[i]);
         write(ffile, buffer, strlen(buffer));
         size *= p->dim[i];
      }
      write(ffile, "\n", 1);
      if (p->type == DA) {
         data *dp;
         dp = p->datap;
         write(ffile, dp, size*sizeof(data));
      }
      else {
         write(ffile, (char *)p->datap, size);
         write(ffile, "\n", 1);
      }
      break;

      case NF:
      write(ffile, "NF ", 3);
      goto real;

      case MF:
      write(ffile, "MF ", 3);
      goto real;

      case DF:
      write(ffile, "DF ", 3);
real:
      write(ffile, an->namep, strlen(an->namep));
      write(ffile, "\n", 1);
      lseek(wfile,(long)an->label,0);
      while (1) {
         read(wfile, &c, 1);
         write(ffile, &c, 1);
         if (c == 0) break;
      }
      break;
   }
   return 0;
}

