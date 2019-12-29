/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "userfunc.h"
#include "main.h"
#include "memory.h"

/* List a function on the terminal */
void ex_list() {
    SymTabEntry* function;
    int line;
    int i;

    /* Check for valid function */

    function = (SymTabEntry*)*--sp;
    if (function->entryType != LV)
        error(ERR_value, "function name not defined");

    /* If a function, locate it in workspace file and
    * print on the terminal in formatted form.
    */

    switch (function->entryUse) {
    default:
        error(ERR_botch, "cannot find requested function");

    case NF:
    case MF:
    case DF:
        for (line = 0; line < function->sourceCodeCount; ++line) {
            char *lineText = function->functionSourceCode[line];

            if (line == 0) {
                printf("     ");
            } else {
                printf("[%d]  ", line);
            }

            if (ascii_characters) {
                char *ascii_line = toAplTouchtypeLine(lineText);
                if (ascii_line == NULL) {
                    error(ERR, "list:  memory failure");
                }

                printf("%s", ascii_line);

                aplfree((int *) ascii_line);

            } else {
                int len = strlen(lineText);

                for (i = 0; i < len-1; ++i) {
                    printf("%c", lineText[i]);
                }
            }
        }
    }
}
