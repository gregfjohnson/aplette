/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "apl.h"
#include "data.h"
#include "debug.h"
#include "userfunc.h"
#include "main.h"

/* print line and error pointer */
void pline(char* str, int loc, int ln)
{
    int c, l;
    l = 0;

    // maybe some day..
    #if 0
        /* print line number if applicable */
        if (ln >= 0) {
            printf("[%d]\t", ln - 1);
            loc += 8;
            l += 8;
        }
        else
            printf("\t");
    #endif

    /* print the line */
    do {
        c = *str++;
        l++;
        putAplTouchtypeChar(c);
    } while (c != '\n');

    // maybe some day..
    #if 0
        /* print the error pointer under the line */
        printf("\t");
        for (l = 1; l < loc; l++)
            printf(" ");
        printf("^\n");
    #endif
}

void error(int type, char* diagnostic)
{
    intflg = 0;
    if (ifile) {
        close(ifile);
        ifile = 0;
    }

    switch (type) {
    case ERR:
        printf("Error");
        break;

    case ERR_axis:
        printf("Axis Error");
        break;

    case ERR_domain:
        printf("Domain Error");
        break;

    case ERR_implicit:
        printf("Implicit Error");
        break;

    case ERR_index:
        printf("Index Error");
        break;

    case ERR_length:
        printf("Length Error");
        break;

    case ERR_limit:
        printf("Limit Error");
        break;

    case ERR_rank:
        printf("Rank Error");
        break;

    case ERR_syntax:
        printf("Syntax Error");
        break;

    case ERR_value:
        printf("Value Error");
        break;

    case ERR_interrupt:
        printf("Interrupt");
        break;

    case ERR_botch:
        printf("Botch Error");
        break;

    case ERR_security:
        printf("Security Violation");
        break;

    default:
        printf("Panic, unknown error type");
    }

    if (strncmp(diagnostic, "", 80) == 0)
        printf(".\n");
    else
        printf(": %s.\n", diagnostic);

    if (vars_trace)
        vars_dump();

    /* produce traceback and mark state indicator */
    tback(0);

    if (state_indicator_ptr->Mode == deffun) {
        state_indicator_ptr->suspended = 1;
    }
    else {
        while (expr_stack_ptr > expr_stack)
            pop(); /* zap garbage */
    }
    mainloop();
}
