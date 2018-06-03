/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "execute.h"

/* execute dyadic scalar functions
 * this routine is called from execute() 
 * 'm' indicates whether the function may or not operate with char
 * this routine makes a decision and passes control to
 * one of the specialist routines:
 * * ex_cdyad - character dyadic
 * * ex_ddyad - floating point dyadic (ie type d)
 * * ex_mdyad - mixed dyadic
 */
void ex_dscal(int m, int (*f)(), struct item* p1, struct item* p2)
{
    if (p1->itemType != p2->itemType) {
        if (m == 2)
            ex_mdyad((data (*)()) f, p1, p2); /* modified 9.8.1999/tyl */
        else
            error(ERR_domain, "dscal - types do not match");
    }
    else if (p1->itemType == CH) {
        if (m)
            ex_cdyad(f, p1, p2);
        else
            error(ERR, "dscal - type panic");
    }
    else
        ex_ddyad(f, p1, p2);
}
