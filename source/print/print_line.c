/* print_line.c, Copyright (C) 2018, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <string.h>
#include "main.h"

void printLine(char *line) {
    int i;
    int len = strlen(line);

    for (i = 0; i < len; ++i) {
        putAplTouchtypeChar(line[i]);
    }
}
