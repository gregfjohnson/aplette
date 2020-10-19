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

/* f is execution flag:
 *   0 compile immediate
 *   1 compile quad input
 *   2 function definition
 *   3 function prolog
 *   4 function epilog
 *   5 function body
 */
// these constants are defined in apl.y.
// they correspond to the CompilePhase enum,
// values of which are passed into compile_new()
// as an argument.
//
// They are used to create fake lexemes that
// guide the behavior of the parser.
// (there are cases in which the same syntax needs
// to be treated // differently depending on the context in
// which it is being compiled.)
//
int ilex[] = {
    compile_immed,
    compile_quad_input,
    compile_function_defn,
    compile_function_prolog,
    compile_function_epilog,
    compile_function_body
};

char* compile_new(int f) {
    char *p, *q;

    iline = state_indicator_ptr->text;
    ccharp = oline;
    litflag = 0;
    nlexsym = ilex[f];
    context = nlexsym;
    compilePhase = (CompilePhase) f;

    if (code_trace) {
        char *line = toAplTouchtypeLine(iline);
        fprintf(stderr, "\n\nabout to yyparse.. iline:  >>%s<<\n\n", line);
        aplfree(line);
    }

    if (yyparse()) {
        //print line and error pointer
        pline(state_indicator_ptr->text, iline - (state_indicator_ptr->text), lineNumber);
        return (0);
    }

    *ccharp++ = END;

    parseDump(oline, ccharp - oline);

    iline = (char*) alloc(ccharp - oline);

    p = iline;
    for (q = oline; q < ccharp; ++q)
        *p++ = *q;

    state_indicator_ptr->pcode = iline;

    return (iline);
}
