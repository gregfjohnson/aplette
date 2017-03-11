/* readline.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <string.h>
#include "apl.h"
#include "main.h"
#include "memory.h"

static char line[LINEMAX];

char* readLine(char* title, char* xLine, int xLineLength, FILE* xInfile) {
    char* status = NULL;
    char* asciiLine;
    int i, len;

    if (xLineLength < 1)
        goto done;

    if (ascii_characters) {
        status = fgets(line, LINEMAX, xInfile);
        if (status == NULL)
            goto done;

        // did we read a whole line??
        if (line[strlen(line) - 1] != '\n') {
            status = NULL;
            goto done;
        }

        asciiLine = to_ascii_input(line);
        if (asciiLine == NULL)
            goto done;

        len = strlen(asciiLine);
        if (len > xLineLength - 1)
            len = xLineLength - 1;

        for (i = 0; i < len; ++i) {
            xLine[i] = asciiLine[i];
        }
        xLine[i] = '\0';

        aplfree((int*)asciiLine);

    } else {
        status = fgets(xLine, xLineLength, xInfile);

        // did we read a whole line??
        if (status != NULL && xLine[strlen(xLine) - 1] != '\n') {
            status = NULL;
            goto done;
        }
    }

done:
    if (code_trace) {
        if (status) {
            fprintf(stderr, "%s; input line:  %s\n", title, xLine);

        } else {
            fprintf(stderr, "%s; input line:  <no data read>\n", title);
        }
    }

    return status;
}
