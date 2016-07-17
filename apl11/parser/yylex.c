/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"
#include "char.h"
#include "y.tab.h"
#include "opt_codes.h"

#define lv yylval
#define v yyval

extern struct OPER tab[];

int xxpeek[2] = { 0, 0 };

int yylex()
{
    int result;
    int c, rval;
    struct OPER* tp;

    if (nlexsym != -1) { /* first token is lexical context */
        c = nlexsym;
        nlexsym = -1;
        result = c;
        goto done;
    }
    while (litflag > 0) { /* comment */
        c = *iline++;
        if (c == '\n') {
            nlexsym = 0;
            result = eol;
            goto done;
        }
    }
    if (xxpeek[0] != 0) {
        lv.charval = xxpeek[0]; /* may want charptr here */
        xxpeek[0] = 0;
        result = xxpeek[1];
        goto done;
    }
    do
        c = *iline++;
    while (c == ' ');
    if (c == '\n') {
        nlexsym = 0;
        result = eol;
        goto done;
    }

    if (alpha(c)) {
        result = getnam(c);
        goto done;
    }

    if (digit(c) || c == C_OVERBAR || (c == '.' && digit(*iline))) {
        result = getnum(c);
        goto done;
    }
    /* C_OVERBAR is the negative number prefix */

    rval = unk;
    for (tp = tab; tp->input; tp++) {
        if (tp->input == c) {
            lv.charval = tp->lexval;
            rval = tp->retval;
            break;
        }
    }
    /* If it's a comment, skip to the end
    * of the line and return eol instead.  */
    if (lv.charval == COMNT) {
        while (1) {
            c = *iline++;
            if (c == '\n') {
                nlexsym = 0;
                result = eol;
                goto done;
            }
        }
    }

    if (lv.charval == QUAD) {
        result = getquad();
        goto done;
    }

    result = rval;

done:

    return result;
}
