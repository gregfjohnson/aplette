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
#include "utility.h"
#include "format.h"
#include "data.h"
#include "memory.h"

/* dyadic format for floating point data */

struct item* fp_dfmt(struct item* f, struct item* p)
{
    char *charptr, *buffer;
    struct item* q;
    int i, j, k, total, ncol, nrow, rowsz;
    struct FORMAT *format_list, *format, *format_next;
    data *dp, *df;

    ncol = p->rank ? p->dim[p->rank - 1] : 1;

    /* Check validity of format list. */
    if (f->rank > 1 || f->size <= 1 || (f->size != 2 && f->size != 2 * ncol))
        error(ERR_length, "");

    /* create the format list */
    df = f->datap;
    for (i = 0; i < ncol; i++) {
        format_next = (struct FORMAT*)alloc(sizeof(struct FORMAT));
        if (i == 0) {
            format_list = format_next;
        }
        else {
            format->next = format_next;
        }
        format = format_next;

        /* populate the format list */
        format->sign = 0;
        format->left_ratn = 0;
        format->right_ratn = 0;
        format->pp_ratn = PrintP;
        format->left_expn = 0;
        format->right_expn = 0;
        format->digit_expn = 0;

        format->digits = (int)*df;
        //printf("%f %f\n",*df,*(df+1));
        if (*(df + 1) < 0) { // exponential format
            format->exp = 1;
            format->digits = (int)*df;
            format->sign = 1;
            format->right_expn = (int)(-*(df + 1) - 1);
        }
        else { // rational format
            format->exp = 0;
            format->digits = (int)*df;
            format->right_ratn = (int)*(df + 1);
            format->left_ratn = format->digits - format->right_ratn;
        }
        /* adjust pointer to format spec */
        if (f->size == 2)
            df = f->datap;
        else
            df += 2;
    }

    /* Work out the number of rows */
    nrow = 0;
    for (i = 1; i <= p->size; i++) {
        if (i % ncol == 0) {
            nrow += 1;
        }
    }

// for debugging purposes only
#if 0
   format=format_list;
   for(i=0; i<ncol; i++) {
      printf("s %d, e %d, l_r %d, r_r %d, pp %d, l_e %d, r_e %d, d_e %d, dig %d\n",
      format->sign, format->exp,
      format->left_ratn, format->right_ratn, format->pp_ratn,
      format->left_expn, format->right_expn, format->digit_expn,
      format->digits);

      format=format->next;
   }
#endif

    dp = p->datap;
    bidx(p);

    /* find the maximum number of chars in any row */
    format = format_list;
    rowsz = 0;
    for (i = 0; i < ncol; i++) {
        rowsz += format->digits;
        //rowsz+=1;	//inter column space
        format = format->next;
    }
    //rowsz+=-1;	//no inter column space on last element

    /* adjust nrow - add a blank line every time that an array
    * starts on a new dimension.
    */
    for (i = 0; i < p->rank - 2; i++) {
        for (j = 0, k = 1; j <= i; j++)
            k *= p->dim[j];
        nrow += k - 1; //...but no blank lines on the very last array
    }

    /* calculate total number of characters */
    total = nrow * rowsz;

    /* make new data */
    if (p->rank >= 2) {
        q = newdat(CH, 2, total);
        q->dim[0] = nrow;
        q->dim[1] = rowsz;
    }
    else {
        q = newdat(CH, 1, total);
        q->dim[0] = rowsz;
    }

    /* fill data area with blanks */
    charptr = (char*)(q->datap);
    for (i = 0; i < total; i++)
        *charptr++ = ' ';

    /* fill it up with data */
    dp = p->datap;
    charptr = (char*)(q->datap);
    format = format_list;

    for (i = 1; i <= p->size; i++) {
        buffer = fp2char_paded(*dp++, format);
        //printf("<%s>\n",buffer);
        for (k = 0; k < format->digits; k++)
            *charptr++ = *buffer++;
        //if (i%ncol !=0 ) *charptr++='#' ;	// inter-column spacing

        /* has end of dimension been reached? */
        if (i != p->size) {
            for (j = p->rank - 3; j >= 0; j--) {
                if (i % idx.del[j] == 0) {
                    charptr += rowsz;
                }
            }
        }
        if (i % ncol == 0)
            format = format_list;
        else
            format = format->next;
    }

    /* release the format list */
    format = format_list;
    for (i = 0; i < ncol; i++) {
        format_next = format->next;
        aplfree(format);
        format = format_next;
    }

    return (q);
}
