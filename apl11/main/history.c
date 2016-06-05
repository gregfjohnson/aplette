/* history.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include "config.h"

#ifdef HAVE_LIBREADLINE
    #include <readline/history.h>

    void readline_add_history(char *line) {
        add_history(line);
    }
#else
    void readline_add_history(char *line) {
    }
#endif
