/* utility.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef UTILITY_H
#define UTILITY_H
#include "apl.h"

void error(int type, char *diagnostic);
int topfix();
int scalar(struct item *aip);
void pline(char *str, int loc, int ln);
int fix(data d);
void checksp();
void fppinit(int arg);
int fuzz(data d1, data d2);
void map(int o);
void iodone(int ok);
int empty(int fd);
int opn(char file[], int rw);

void intr(int s);
void panic(int signum);
void catchsigs();

#endif // UTILITY_H
