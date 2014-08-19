/* openAPL, Copyright (C) Branko Bratkovic 1999
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */

#include "apl.h"
#include "format.h"

/* dyadic format */
void ex_dfmt()
{
   struct item *rp, *lp, *q;
   int ncol;

   lp = fetch2();
   rp = sp[-2];
   ncol = rp->rank ? rp->dim[rp->rank-1] : 1;

   switch (lp->type) {
   case DA:
   break;

   case CH:
      error(ERR_domain,"");
   break;
	     
   default:
      error(ERR_botch,"attempt to format unsupported type");
   }
      
   switch (rp->type) {
   case DA:
      /* convert rp from numeric to a literal array */
      q=fp_dfmt(lp,rp);
      pop();
      pop();
      *sp++ = q; // put it onto the stack
   break;

   case CH:
      error(ERR_domain,"");
   break;
	     
   default:
      error(ERR_botch,"attempt to format unsupported type");
   }
	  
}

