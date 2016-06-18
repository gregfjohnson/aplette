/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "fdat.h"
#include "work_space.h"

int nsave(int ffile, struct nlist *an);

void wssave(int ffile) {
   struct nlist *n;

   nsave(ffile, 0);
   for(n=nlist; n->namep; n++) nsave(ffile, n);
   fdat(ffile);
   close(ffile);
}

int nsave(int ffile, struct nlist *an) {
   char c, buffer[64];
   int i, size;
   struct item *p;

   if (an == 0){
      writeErrorOnFailure(ffile, "apl\\11\n", 7);
      sprintf(buffer, "tolerance %lg\n", tolerance);
      writeErrorOnFailure(ffile, buffer, strlen(buffer));
      sprintf(buffer, "origin %d\n", iorigin);
      writeErrorOnFailure(ffile, buffer, strlen(buffer));
      sprintf(buffer, "width %d\n", pagewidth);
      writeErrorOnFailure(ffile, buffer, strlen(buffer));
      sprintf(buffer, "digits %d\n", PrintP);
      writeErrorOnFailure(ffile, buffer, strlen(buffer));
      return 0;
   }

   if (an->use == 0 || (an->use == DA && an->itemp == 0)) return 0;

   switch (an->use) {
      default:
      close(ffile);
      error(ERR_botch,"type is unknown");

      case DA:
      p = an->itemp;
      if (p->type == DA) writeErrorOnFailure(ffile, "DA ", 3);
      else writeErrorOnFailure(ffile, "CH ", 3);
      writeErrorOnFailure(ffile, an->namep, strlen(an->namep));
      sprintf(buffer, " %d", p->rank);
      writeErrorOnFailure(ffile, buffer, strlen(buffer));
      size = 1;
      for (i=0; i<p->rank; i++) {
         sprintf(buffer, " %d", p->dim[i]);
         writeErrorOnFailure(ffile, buffer, strlen(buffer));
         size *= p->dim[i];
      }
      writeErrorOnFailure(ffile, "\n", 1);
      if (p->type == DA) {
         data *dp;
         dp = p->datap;
         writeErrorOnFailure(ffile, dp, size*sizeof(data));
      }
      else {
         writeErrorOnFailure(ffile, (char *)p->datap, size);
         writeErrorOnFailure(ffile, "\n", 1);
      }
      break;

      case NF:
      writeErrorOnFailure(ffile, "NF ", 3);
      goto real;

      case MF:
      writeErrorOnFailure(ffile, "MF ", 3);
      goto real;

      case DF:
      writeErrorOnFailure(ffile, "DF ", 3);
real:
      writeErrorOnFailure(ffile, an->namep, strlen(an->namep));
      writeErrorOnFailure(ffile, "\n", 1);
      lseek(wfile,(long)an->label,0);
      while (1) {
         readErrorOnFailure(wfile, &c, 1);
         writeErrorOnFailure(ffile, &c, 1);
         if (c == 0) break;
      }
      break;
   }
   return 0;
}

