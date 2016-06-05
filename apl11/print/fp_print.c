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
#include "data.h"
#include "memory.h"

/* print floating point */

int fp_print(struct item *p)
{
   data *dp;
   int i, j, k, ncol;
   struct FORMAT *format_list, *format, *format_next;

   ncol = p->rank ? p->dim[p->rank-1] : 1;

   /* create the format list */
   for (i=0; i<ncol; i++) {
      format_next=(struct FORMAT *)alloc(sizeof(struct FORMAT));
      if (i==0) {
         format_list=format_next;
      }
      else {
         format->next=format_next;
      }
      format=format_next;
      /* zeroize size information vector */
      format->sign=0;
      format->exp=0;
      format->left_ratn=0;
      format->right_ratn=0;
      format->pp_ratn=PrintP;
      format->left_expn=0;
      format->right_expn=0;
      format->digit_expn=0;
      format->digits=0;
   }

   /* Use "fp_digits()" to figure out the maximum field width
    * required by any of the values to be printed.
    */
   dp = p->datap;
   format=format_list;
   for(i=1; i<=p->size; i++) {
      fp_digits(*dp++, format);
      if (i%ncol == 0) format=format_list ;
      else format=format->next;
   }

   /* calculate the total number of digits */
   format=format_list;
   for(i=0; i<ncol; i++) {
      if (format->exp == 0 ){ 
         format->digits=format->left_ratn+format->right_ratn;
	 if(format->right_ratn !=0) format->digits++;	//decimal point
      }
      else {
         format->digits=format->left_expn+format->right_expn+format->digit_expn;
	 if(format->right_expn !=0) format->digits++;	//decimal point
      }

      /* for debugging purposes only
      printf("s %d, e %d, l_r %d, r_r %d, pp %d, l_e %d, r_e %d, d_e %d, dig %d\n",
      format->sign, format->exp,
      format->left_ratn, format->right_ratn, format->pp_ratn,
      format->left_expn, format->right_expn, format->digit_expn,
      format->digits); /**/

      format=format->next;
   }

   dp = p->datap;
   bidx(p);

   format=format_list;
   for(i=1; i<=p->size; i++) {
      if(intflg) break;
      if(format->digits+column >= pagewidth ) {
         putchar('\n');
         column=0;
         for(k=0; k<9; k++, column++) putchar(' ');
      }
      column+=printf("%s",fp2char(*dp++, format));
      if (i%ncol !=0 ) column+=printf(" "); // inter-column spacing
	     

      /* has end of dimension been reached? */
      if (i != p->size ) {
	 for(j=p->rank-2; j>=0; j--) {
            if(i%idx.del[j] == 0) {
               putchar('\n');
               column=0;
            }
         }
      }
      if (i%ncol == 0) format=format_list ;
      else format=format->next;
   }

   /* release the format list */
   format=format_list;
   for (i=0; i<ncol; i++) {
      format_next=format->next;
      aplfree(format);
      format=format_next;
   }

   return(1);
}

