/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <sys/times.h>
#include "apl.h"
#include "utility.h"
#include "data.h"

int afnfree, afnused;

void ex_mibm() {
    struct tm* localtime();
    Context* gp;
    item_t* p;
    int i;
    struct tms t;

    switch (topfix()) {
        default:
            error(ERR_implicit, "unknown i-beam");

        case 1: /* toggle code trace */
            datum = code_trace;
            code_trace = !code_trace;
            break;

        case 2: /* toggle expr_stack trace */
            datum = stack_trace;
            stack_trace = !stack_trace;
            break;

        case 3: /* toggle memory trace */
            datum = mem_trace;
            mem_trace = !mem_trace;
            break;

        case 4: /* toggle variables trace */
            datum = vars_trace;
            vars_trace = !vars_trace;
            break;

        case 5: /* toggle function trace */
            datum = funtrace;
            funtrace = !funtrace;
            break;

        case 21: /* CPU time */
            times(&t);
            datum = t.tms_utime + t.tms_stime;
            break;

        case 22: /* ws bytes unused */
            datum = afnfree;
            break;

        case 26: /* current line */
            if (state_indicator_ptr->Mode == deffun)
                datum = state_indicator_ptr->funlc - 1;
            else
                datum = 0;
            break;

        case 27: /* vector of line numbers of fn activations # */
            i = 0;
            gp = state_indicator_ptr;
            while (gp) {
                if (gp->np)
                    i++;
                gp = gp->prev;
            }
            p = newdat(DA, 1, i);
            gp = state_indicator_ptr;
            i = 0;
            while (gp) {
                if (gp->np)
                    ;
                p->datap[i++] = gp->funlc - 1;
                gp = gp->prev;
            }
            *expr_stack_ptr++ = p;
            return;

        /*
        * non standard I functions
        */

        case 32: /* ws bytes in use */
            datum = afnused;
            break;

        case 36: /* 2nd element of ib27 */
            if ((state_indicator_ptr->Mode == deffun) && state_indicator_ptr->prev->Mode == deffun)
                datum = state_indicator_ptr->prev->funlc - 1;
            else
                datum = 0;
            break;

        case 40: /* Total accumulated child's time */
            times(&t);
            datum = t.tms_cutime + t.tms_cstime;
            break;

        case 41: /* Total accumulated user time -- including all kids */
            times(&t);
            datum = t.tms_utime + t.tms_cutime;
            break;

        case 42: /* Total system time -- including all kids */
            times(&t);
            datum = t.tms_stime + t.tms_cstime;
            break;

        case 43: /* User time -- parent only */
            times(&t);
            datum = t.tms_utime;
            break;

        case 44: /* System time -- parent only */
            times(&t);
            datum = t.tms_stime;
            break;
    }
    p = newdat(DA, 0, 1);
    p->datap[0] = datum;
    *expr_stack_ptr++ = p;
}
