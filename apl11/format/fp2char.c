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
#include "format.h"

/* convert floating point data d to character string */
char* fp2char(data d, struct FORMAT* format)
{
    double value;
    int sign, width, d_places, n, m;

    value = d;

    if (format->exp == 0) { //rational format applies
        width = format->digits;
        d_places = format->right_ratn;
        sprintf(format_buffer, "%*.*f", width, d_places, value);
        /* leading spaces */
        for (n = 0; format_buffer[n] == ' '; n++)
            ;
        /* leading minus */
        if (format_buffer[n] == '-')
            format_buffer[n++] = C_OVERBAR;
        /* leading zeros and decimal place */
        for (; format_buffer[n] == '0' || format_buffer[n] == '.'; n++)
            ;
        /* count out PrintP digits */
        for (m = 0; m < format->pp_ratn && n < width;) {
            if (format_buffer[n] != '.')
                m++;
            n++;
        }
        /* remove trailing zeros */
        if (n > format->left_ratn) {
            for (; format_buffer[n - 1] == '0'; n--)
                ;
            if (format_buffer[n - 1] == '.')
                n--;
        }
        /* add trailing spaces */
        for (; n < width; n++)
            format_buffer[n] = ' ';
    }

    else { //exponential format applies
        sign = format->sign;
        width = format->digits - sign;
        d_places = format->right_expn;
        /* leading minus */
        if (sign) {
            if (value < 0) {
                format_buffer[0] = C_OVERBAR;
                value = -value;
            }
            else
                format_buffer[0] = ' ';
            n = 1;
        }
        else
            n = 0;
        /* special case of 0 */
        if (value == 0) {
            format_buffer[n++] = '0';
            format_buffer[n++] = 'E';
            format_buffer[n++] = '0';
            for (; n < format->digits; n++)
                format_buffer[n] = ' ';
            format_buffer[n] = '\0';
            return (char*)&format_buffer;
        }

        /* use printf to create the raw value */
        sprintf(format_buffer + sign, "%*.*e", width, d_places, value);
        //printf("<%s>\n",format_buffer);
        /* point m to the e in the exponent */
        m = format->right_expn + 2 + sign;
        //printf("%c\n",format_buffer[m]);
        if (format->right_expn == 0)
            m--; //compensate for lack of dp
        /* remove trailing zeros */
        for (n = m; format_buffer[n - 1] == '0'; n--)
            ;
        if (format_buffer[n - 1] == '.')
            n--;
        if (format_buffer[n - 1] == 'e')
            n--;
        /* move the E forward */
        format_buffer[n++] = 'E';
        m++;
        /* deal with exponent sign */
        if (format_buffer[m++] == '-')
            format_buffer[n++] = C_OVERBAR;
        /* skip exponent leading zeros */
        for (; format_buffer[m] == '0'; m++)
            ;
        if (format_buffer[m] == '\0')
            format_buffer[n++] = '0';
        /* move the exponent digits forward */
        for (; format_buffer[m] != '\0';)
            format_buffer[n++] = format_buffer[m++];
        /* fill with trailing blanks */
        for (; n < format->digits; n++)
            format_buffer[n] = ' ';
        format_buffer[n] = '\0';
    }
    return (char*)&format_buffer;
}
