/* main.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

void mainloop();
void Exit(int s);

char* to_ascii_input(char* input);
void putAplTouchtypeChar(char c);

#endif
