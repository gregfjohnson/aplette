/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "utility.h"
#include "local_parser.h"
#include "y.tab.h"
#include "opt_codes.h"
#include "memory.h"
#include "debug.h"
#include "ascii_input.h"

/* s is statement
 * f is execution flag:
 *   0 compile immediate
 *   1 compile quad input
 *   2 function definition
 *   3 function prolog
 *   4 function epilog
 *   5 function body
 */
extern int ilex[];

char* compile_old(char* s, int f)
{
    int i;

    iline = s;
    ccharp = oline;
    litflag = 0;
    nlexsym = ilex[f];
    context = nlexsym;
    compilePhase = (CompilePhase)f;

    if (code_trace) {
        char *line = toAplTouchtypeLine(iline);
        fprintf(stderr, "\n\nabout to yyparse.. iline:  >>%s<<\n\n", line);
        aplfree(line);
    }

    if (yyparse()) {
        pline(s, iline - s, lineNumber); //print line and error pointer
        return (0);
    }
    *ccharp++ = END;

    parseDump(oline, ccharp - oline);

    iline = (char*) alloc(ccharp - oline);

    for (i = 0; i < ccharp - oline; ++i) {
        iline[i] = oline[i];
    }

    return (iline);
}
