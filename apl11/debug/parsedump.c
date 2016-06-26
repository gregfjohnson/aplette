/* parsedump.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include "apl.h"

void parseDump(char *line, int len) {
    int i;

    if (!code_trace) return;

    for (i = 0; i < len; ++i) {
        fprintf(stderr, "%02x ", 0xff & line[i]);
    }
    fprintf(stderr, "\n");
}
