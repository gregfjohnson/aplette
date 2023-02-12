/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdio.h>
#include "apl.h"
#include "data.h"
#include "char.h"
#include "utility.h"
#include "memory.h"
#include "opt_codes.h"

/* The fetch routines are used to convert dummy types into 
 * real data.  For instance, a quad variable may be put
 * onto the expr_stack, when it comes time to use it, fetch()
 * will convert it into a float (ie DA) or character (ie CH).
 * fetch1() and fetch2() are used to deal with the top and
 * top two expr_stack entries respectively. - bb
 */

item_t* fetch1()
{
    item_t* p;

    p = fetch(expr_stack_ptr[-1]);
    expr_stack_ptr[-1] = p;
    return (p);
}

item_t* fetch2()
{
    item_t* p;

    expr_stack_ptr[-2] = fetch(expr_stack_ptr[-2]);
    p = fetch(expr_stack_ptr[-1]);
    expr_stack_ptr[-1] = p;
    return (p);
}

item_t* fetch(item_t* ip)
{
    item_t *p, *q;
    int i;
    extern int prolgerr;

    p = ip;

loop:
    switch (p->itemType) {

    case NIL:
        if (lastop != PRINT)
            error(ERR_value, "right value is NIL");
        return (p);

    case QV: {        /* Quad Variables */
        item_t *(*quadServiceRoutine)(int);

        i = p->index; /* get the pointer to applicable quad service routine */
        aplfree(p);
        quadServiceRoutine = (item_t *(*)(int)) exop[i];
        p = quadServiceRoutine(0);
        goto loop;
    }

    case DA: /* DAta type */
    case CH: /* CHaracter type */
        p->index = 0;
        return (p);

    case LV:

        /* KLUDGE --
       *
       * Currently, if something prevents APL from completing
       * execution of line 0 of a function, it leaves with
       * the expr_stack in an unknown state and "state_indicator_ptr->oldsp" is
       * zero.  This is nasty because there is no way to
       * reset out of it.  The principal cause of error
       * exits from line 0 is the fetch of an undefined
       * function argument.  The following code attempts
       * to fix this by setting an error flag and creating
       * a dummy variable for the expr_stack if "used before set"
       * occurs in the function header.  "ex_fun" then will
       * note that the flag is high and cause an error exit
       * AFTER all header processing has been completed.
       */

        if (((SymTabEntry*)p)->entryUse != DA) {
            if ((state_indicator_ptr->Mode != deffun) || state_indicator_ptr->funlc != 1)
                error(ERR_value, "undefined variable");
            q = newdat(DA, 0, 1); /* Dummy */
            q->datap[0] = 0;
            prolgerr = 1; /* ERROR flag */
            return (q);
        }
        p = ((SymTabEntry*)p)->itemp;
        i = p->itemType;
        if (i == LBL)
            i = DA; /* treat label as data */
        q = newdat(i, p->rank, p->size);
        copy(IN, (char*)p->dim, (char*)q->dim, p->rank);
        copy(i, (char*)p->datap, (char*)q->datap, p->size);
        return (q);

    default:
        error(ERR_botch, "fetch");
    }
    return NULL; // never reached because of default above..
}
