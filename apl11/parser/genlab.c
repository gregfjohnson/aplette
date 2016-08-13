/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"
#include "opt_codes.h"
#include "data.h"

/*
 * genlab -- generates label code onto label stacks.
 *
 * prologue:   AUTO-lab, CONST-linenum, NAME-lab LABEL END
 *
 * epilog:   REST-lab END
 */
void genlab(SymTabEntry* np) {
    data lnumb;

    // label prologue

    *labcpp++ = AUTO;
    labcpp += copy(PTR, (char*)&np, (char*)labcpp, 1);

    *labcpp++ = CONST;
    *labcpp++ = 1;
    lnumb = (data)lineNumber;
    labcpp += copy(DA, (char*)&lnumb, (char*)labcpp, 1);

    *labcpp++ = NAME;
    labcpp += copy(PTR, (char*)&np, (char*)labcpp, 1);

    *labcpp++ = LABEL;

    *labcpp = END;

    // label epilog

    *labcpe++ = REST;
    labcpe += copy(PTR, (char*)&np, (char*)labcpe, 1);

    *labcpe = END;
}
