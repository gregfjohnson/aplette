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
void ex_dscal(int m, data (*f)(), item_t* p1, item_t* p2)
{
    if (p1->itemType != p2->itemType) {
        if (m == 2) {
            // true for operators "=" and not_equal.
            // only case where operand types can be different.
            ex_mdyad((data (*)()) f, p1, p2);

        } else {
            error(ERR_domain, "dscal - types do not match");
        }

    } else if (p1->itemType == CH) {
        if (m) {
            ex_cdyad((data (*)()) f, p1, p2);

        } else {
            error(ERR, "dscal - type panic");
        }

    } else {
        ex_ddyad((data (*)()) f, p1, p2);
    }
}
