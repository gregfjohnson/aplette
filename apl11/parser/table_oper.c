/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "char.h"
#include "local_parser.h"
#include "y.tab.h"
#include "opt_codes.h"

/* This table defines the operators in APL\11.
 * The first entry is the character representing
 * the operator, the second is the unique operator
 * identifier (which should give you a hint as
 * to what the operator is), and the third is
 * the operator type, of interest only to the
 * interpreter.
 *
 * Note: What isn't shown here is that C_OVERBAR,
 * ie negative number prefix
 * is hardcoded upon input in lex.c 
 * and upon output in print.c
 */

struct OPER tab[] = {
    /*
 * one of a kind
 */
    {
        '(', unk, lpar,
    },
    {
        ')', unk, rpar,
    },
    {
        '[', unk, lbkt,
    },
    {
        ']', unk, rbkt,
    },
    {
        '/', COM, com,
    },
    {
        C_DEL, unk, dell,
    },
    {
        C_SLASHBAR, COM0, com0,
    },
    {
        '\\', EXD, com,
    },
    {
        C_SLOPEBAR, EXD0, com0,
    },
    {
        '\'', unk, strng,
    },
    {
        C_JOT, unk, null,
    },
    {
        '.', IPROD, dot,
    },
    {
        C_QUAD, QUAD, q_var,
    },
    {
        C_QUOTEQUAD, QQUAD, q_var,
    },
    {
        ';', unk, semi,
    },
    {
        ':', unk, cln,
    },
    {
        C_UPSHOEJOT, COMNT, comnt,
    },
    {
        C_RIGHTARROW, BRAN0, tran,
    },

    /*
 * dyadic scalars
 *   op2 op1 v (dyadic op)
 */

    {
        '<', LT, dscal,
    },
    {
        '>', GT, dscal,
    },
    {
        C_LESSOREQUAL, LE, dscal,
    },
    {
        C_GRATOREQUAL, GE, dscal,
    },
    {
        '=', EQ, dscal,
    },
    {
        C_NOTEQUAL, NE, dscal,
    },
    {
        '^', AND, dscal,
    },
    {
        C_OR, OR, dscal,
    },
    {
        C_NAND, NAND, dscal,
    },
    {
        C_NOR, NOR, dscal,
    },

    /*
 * monadic or dyadic scalars
 *   op2 op1 v (dyadic op)
 *   op1 v+1 (monadic op)
 */

    {
        '+', ADD, mdscal,
    },
    {
        '-', SUB, mdscal,
    },
    {
        C_MULTIPLY, MUL, mdscal,
    },
    {
        C_DIVIDE, DIV, mdscal,
    },
    {
        C_STILE, MOD, mdscal,
    },
    {
        C_DOWNSTILE, MIN, mdscal,
    },
    {
        C_UPSTILE, MAX, mdscal,
    },
    {
        '*', PWR, mdscal,
    },
    {
        C_CIRCLESTAR, LOG, mdscal,
    },
    {
        C_CIRCLE, CIR, mdscal,
    },
    {
        '!', COMB, mdscal,
    },

    /*
 * monadic
 *   op1 v (monadic op)
 */

    {
        '~', NOT, m,
    },
    {
        C_UPTACKJOT, EPS + 1, m,
    },

    /*
 * dyadic
 *   op2 op1 v (dyadic op)
 */

    {
        C_DOWNTACK, REP, d,
    },
    {
        C_UPARROW, TAKE, d,
    },
    {
        C_DOWNARROW, DROP, d,
    },
    {
        C_LEFTARROW, ASGN, asg,
    },

    /*
 * monadic or dyadic
 *   op2 op1 v (dyadic op)
 *   op1 v+1 (monadic op)
 */

    {
        C_EPSILON, EPS, md,
    },
    {
        C_UPTACK, BASE, md,
    },
    {
        '?', DEAL, md,
    },
    {
        C_RHO, DRHO, md,
    },
    {
        C_IOTA, DIOT, md,
    },
    {
        C_CIRCLEBAR, ROT0, md,
    },
    {
        C_CIRCLESLOPE, DTRN, md,
    },
    {
        C_IBEAM, DIBM, md,
    },
    {
        C_QUADDIVIDE, DDOM, md,
    },
    {
        C_DOWNTACKJOT, DFMT, md,
    },

    /*
 * monadic with optional subscript
 *   op1 v (monadic op)
 *   op1 sub v+1 (subscripted monadic op)
 */

    {
        C_DELTASTILE, GDU, msub,
    },
    {
        C_DELSTILE, GDD, msub,
    },

    /*
 * dyadic with optional subscript
 *   op2 op1 v (dyadic op)
 *   op2 op1 sub v+1 (subscripted dyadic op)
 */

    /*
 * monadic or dyadic with optional subscript
 *   op2 op1 v (dyadic op)
 *   op1 v+1 (monadic op)
 *   op2 op1 sub v+2 (subscripted dyadic op)
 *   op1 sub v+3 (subscripted monadic op)
 */

    {
        C_CIRCLESTILE, ROT, mdsub,
    },
    {
        ',', CAT, mdsub,
    },

    /*
 * end of list
 */

    { 0, 0, 0 }
};
