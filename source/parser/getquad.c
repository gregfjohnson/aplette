/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"
#include "y.tab.h"

extern struct QUOD qtab[];
#define lv yylval

int getquad()
{
    char* p1;
    struct QUOD* p2;
    char qbuf[10];

    p1 = qbuf;
    while (alpha(*iline))
        *p1++ = *iline++;
    *p1++ = 0;
    if (*qbuf == 0)
        return (q_var); /* ordinary quad variable*/
    for (p2 = qtab; p2->qname; p2++) {
        if (equal(p2->qname, qbuf)) {
            lv.charval = p2->qtype;
            return (p2->rtype);
        }
    }
    return (unk);
}
