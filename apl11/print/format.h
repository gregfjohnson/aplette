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

struct	FORMAT {
   int sign;	/* 1 if space for a minus sign is required */
   int exp;	/* 1 if exponential format */
   int left_ratn;	/* number of left digits, rational format
			 * ie, sign+left_digits */
   int right_ratn;	/* number of right digits, rational format
			 * ie, right_digits */
   int pp_ratn;		/* Print Precision for rational format*/
   int left_expn;	/* number of left digits, expotential format
			 * ie, sign+1 */
   int right_expn;	/* number of right digits, expotential format */
   int digit_expn;	/* number of digits in exponent inc sign & 'E' */
   int digits;		/* total field width */
   struct FORMAT *next;	/* linked list forward pointer */
};

char format_buffer[80];
//char output_buffer[80];

