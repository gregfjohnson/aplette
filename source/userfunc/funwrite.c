/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>
#include <stdlib.h>

#include "apl.h"
#include "utility.h"
#include "work_space.h"
#include "ascii_input.h"
#include "memory.h"

void write_line(int fd, char *line) {
    char *ascii_line;

    if (ascii_characters) {
        ascii_line = toAplTouchtypeLine(line);
        if (ascii_line == NULL) {
            error(ERR, "funwrite:  memory failure");
        }

        writeErrorOnFailure(fd, ascii_line, strlen(ascii_line));

        aplfree(ascii_line);

    } else {
        writeErrorOnFailure(fd, line, strlen(line));
    }
}

/* creates an ordinary file from a user defined function
 * in order to enable the user to edit it through a subsequent
 * call to a text editor
 */
void funwrite(char* fname) {
    SymTabEntry* n;
    int line, fd1;

    n = (SymTabEntry *) sp[-1];
    sp--;

    if (n->entryType != LV)
        error(ERR_botch, "fnwrite");

    if (fname == 0)
        fname = n->namep;

    fd1 = opn(fname, 0644);

    switch (n->entryUse) {
    /* First time function declaration */
    case 0: {
        printf("[new fn]\n");
        /* We can get away with the following because struct current_line
         * was made global and function editing is only permitted
         * from the keyboard.  If this subroutine were called from
         * []lx or downtack-jot, the input line would not be
         * current_line and the following would break.
         */
        write_line(fd1, gsip->text);

        break;
    }

    /*   Function already defined  */
    case NF:
    case MF:
    case DF:
        for (line = 0; line < n->sourceCodeCount; ++line) {
            write_line(fd1, n->functionSourceCode[line]);
        }
        break;

    default:
        close(fd1);
        error(ERR, "fnwrite");
    }

    close(fd1);
}
