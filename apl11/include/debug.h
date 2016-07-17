/* debug.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef DEBUG_H
#define DEBUG_H

void vars_dump();
void mem_dump();
void code_dump(char* cp, int flag);
void stack_dump();
void parseDump(char* line, int len);

#endif
