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
#include <stdlib.h>

#include "apl.h"
#include "char.h"
#include "format.h"

/* floating point size
 * Determine the number of characters that would be
 * required to print a floating point data d.
 * The elements of *format are adjusted to the maximum of
 * either their old value or the required field width
 * for the new data item.
 */
void fp_digits(data d, struct FORMAT *format) {
   double value;
   int sign,exp_val,digits,n,exp_dig,exp_sign;
   int right_expn,left_expn,right_ratn,left_ratn;

   value = d;

   /* check sign */
   if (value < 0) {
      sign = 1;
      value=-value;
   } 
   else 
      sign = 0;

   /* use sprintf to create the raw number
    * total width is Print Precision plus . e+xxx
    * right digits is Print Precision minus 1
    */
   sprintf(format_buffer, "%*.*e",PrintP+5,PrintP-1,value);

   /* strip away trailing 0's */
   for(right_expn=PrintP; format_buffer[right_expn]=='0'; right_expn--);

   /* less decimal point */
   right_expn--;
   digits=right_expn+1;
    
   /* locate the start of the exponent and convert into int for later */
   n=PrintP+2;
   exp_val=atoi(format_buffer+n);
   exp_dig=0;	//initialise number of digits in exponent

   /* negative exponent symbol? */
   if (format_buffer[n++] == '-') exp_sign=1;
   else exp_sign=0;

   /* strip leading 0's from exponent */
   for (;format_buffer[n]=='0';n++);
    
   /* count the exponent digits */
   for (;format_buffer[n]!='\0';n++,exp_dig++);

   /* special case of 0 */
   if(value==0) {
      exp_dig=1;
      exp_val=0;
      exp_sign=0;
      left_expn=1;
      right_expn=0;
      digits=1;
   }
   /* apply the results to the exponential parameters */
   left_expn=sign+1;
   //right_expn=right_expn+exp_sign+exp_dig;
   if(sign) format->sign=1;
   if(left_expn > format->left_expn) format->left_expn=left_expn;
   if(right_expn > format->right_expn) format->right_expn=right_expn;
   if(exp_sign+exp_dig+1 > format->digit_expn) 
      format->digit_expn=exp_sign+exp_dig+1;

   if(format->exp == 1) {
      return;
   }

   /* in all the following "if" clauses, when exponential format is
    * certain, return from this function without attempting rational
    * format parameters.
    */
   
   /* if there are more than 5 zeros after dp force exponential format */
   if(exp_val < -6 ) {
      format->exp=1;
      return;
   }

   /* if there are more than 5 zeros before dp force exponential format */
   if (exp_val > 4+digits) {
      format->exp=1;
      return;
   }

   /* if rational format would have more than PrintP digits before dp
    * then force exponential format */
   if (exp_val+1 > PrintP) {
      format->exp=1;
      return;
   }

   /* if control has reached this point, rational format is applicable
    * apply the results
    */
   if (exp_val <=0 ) {
      left_ratn=1+sign;
      right_ratn=digits-1-exp_val;
   }
   else {
      left_ratn=exp_val+1+sign;
      right_ratn=digits-1-exp_val;	// if negative it doesn't matter
   }
   if (left_ratn > format->left_ratn) format->left_ratn=left_ratn;
   if (right_ratn > format->right_ratn) format->right_ratn=right_ratn;

   return;
}

