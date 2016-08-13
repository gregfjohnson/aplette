/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "work_space.h"

/* creates an ordinary file from a user defined function
 * in order to enable the user to edit it through a subsequent
 * call to a text editor
 */
void funwrite(char* fname) {
    SymTabEntry* n;
    int line, i, cnt, fd1, fd2;
    char buf[512];

    n = (SymTabEntry*)sp[-1];
    sp--;

    if (n->entryType != LV)
        error(ERR_botch, "fnwrite");

    if (fname == 0)
        fname = n->namep;

    fd1 = opn(fname, 0644);

    switch (n->entryUse) {
    default:
        close(fd1);
        error(ERR, "fnwrite");

        /*   Undefined function -- print that and do nothing  */
        /*   case 0:
        printf("\t[new fn]\n");
        break; */

    /* First time function declaration */
    case 0:
        printf("\t[new fn]\n");
        /* We can get away with the following because struct current_line
         * was made global and function editing is only permitted
         * from the keyboard.  If this subroutine were called from
         * []lx or downtack-jot, the input line would not be
         * current_line and the following would break.
         */
        writeErrorOnFailure(fd1, gsip->text, strlen(gsip->text));
        break;

    /*   Function already defined  */
    case NF:
    case MF:
    case DF:
        for (line = 0; line < n->sourceCodeCount; ++line) {
            writeErrorOnFailure(fd1, n->functionSourceCode[line],
                                     strlen(n->functionSourceCode[line]));
        }
        break;
    }
    close(fd1);
}
