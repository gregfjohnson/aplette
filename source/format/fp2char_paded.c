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
#include "char.h"
#include "print.h"
#include "format.h"

/* convert floating point data d to character string 
 * do not delete trailing zeros
 * pad with blanks to the field width */

char* fp2char_paded(data d, struct FORMAT* format)
{
    double value;
    int width, d_places, n, m;

    value = d;

    if (format->exp == 0) { //rational format applies
        width = format->digits;
        d_places = format->right_ratn;
        n = sprintf(format_buffer, "%*.*f", width, d_places, value);
        if (n <= width) {
            /* leading spaces */
            for (n = 0; format_buffer[n] == ' '; n++)
                ;
            /* leading minus */
            if (format_buffer[n] == '-')
                format_buffer[n++] = c_overbar();
            /* up to decimal place */
            for (; format_buffer[n] != '.' && n < width; n++)
                ;
            /* count out d_places digits */
            for (m = 0; m < format->right_ratn && n < width;) {
                if (format_buffer[n] != '.')
                    m++;
                n++;
            }
        }
        else { // it didn't fit
            for (n = 0; n < format->digits; n++)
                format_buffer[n] = '*';
        }

        /* add trailing spaces */
        for (; n < width; n++)
            format_buffer[n] = ' ';

        /* hack to overcome -0 problem */
        n--;
        for (; format_buffer[n] == '0' || format_buffer[n] == ' ' || format_buffer[n] == '.'; n--)
            ;
        if (format_buffer[n] == c_overbar())
            format_buffer[n] = ' ';
    }

    else { //exponential format applies
        width = format->digits - format->sign;
        d_places = format->right_expn;

        /* use printf to create the raw value */
        sprintf(format_buffer, "%+*.*e", width, d_places, value);

        /* leading sign */
        for (n = 0; format_buffer[n] == ' '; n++)
            ;
        if (format_buffer[n] == '-' && value != 0)
            format_buffer[n++] = c_overbar();
        else
            format_buffer[n++] = ' ';

        /* skip digits */
        for (; format_buffer[n] != 'e'; n++)
            ;

        /* E symbol */
        format_buffer[n++] = 'E';

        /* exponent's sign */
        m = n + 1;
        if (format_buffer[n] == '-')
            format_buffer[n++] = c_overbar();

        /* skip exponent's leading zero */
        for (; format_buffer[m] == '0';)
            m++;
        if (format_buffer[m] == '\0')
            m--;

        /* bring forward remainder of exponent */
        for (; format_buffer[m] != '\0';)
            format_buffer[n++] = format_buffer[m++];

        if (n > format->digits) { // it didn't fit
            for (n = 0; n < format->digits; n++)
                format_buffer[n] = '*';
        }

        /* add trailing spaces */
        for (; n < format->digits; n++)
            format_buffer[n] = ' ';
        format_buffer[n] = '\0';
    }
    return (char*)&format_buffer;
}
