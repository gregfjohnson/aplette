/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"
#include "char.h"
#include "print.h"
#include "y.tab.h"

int getnum(char ic)
{
    double d1, d2;
    int c, n, n1, s, s1;

    s = 0;
    n = 0;
    d1 = 0.;
    c = ic;

    // C_OVERBAR is negative number prefix
    if (c == C_OVERBAR) {
        s++;
        c = *iline++;

    // ascii version of negative number prefix..
    } else if (ascii_characters && c == '`') {
        s++;
        c = *iline++;
        if (c == '`') c = C_OVERBAR;
    }

    while (digit(c)) {
        d1 = d1 * 10. + c - '0';
        c = *iline++;
    }
    if (c == '.') {
        c = *iline++;
        while (digit(c)) {
            d1 = d1 * 10. + c - '0';
            c = *iline++;
            n--;
        }
    }
    if (c == 'e' || c == 'E') {
        s1 = 0;
        n1 = 0;
        c = *iline++;

        // C_OVERBAR is negative number prefix
        if (c == C_OVERBAR) {
            s1++;
            c = *iline++;

        // ascii version of negative number prefix..
        } else if (ascii_characters && c == '`') {
            s1++;
            c = *iline++;
            if (c == '`') c = C_OVERBAR;
        }

        while (digit(c)) {
            n1 = n1 * 10 + c - '0';
            c = *iline++;
        }
        if (s1)
            n -= n1;
        else
            n += n1;
    }
    n1 = n;
    if (n1 < 0)
        n1 = -n1;
    d2 = 1.;
    while (n1--)
        d2 *= 10.;
    if (n < 0)
        d1 /= d2;
    else
        d1 *= d2;
    if (s)
        d1 = -d1;
    iline--;
    datum = d1;
    return (numb);
}
