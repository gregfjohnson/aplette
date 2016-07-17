/* execute.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef EXECUTE_H
#define EXECUTE_H
#include "apl.h"

void execute();
void ex_dscal(int m, int (*f)(), struct item* p1, struct item* p2);

void ex_cdyad(data (*f)(), struct item* ap, struct item** ap1);
void ex_mdyad(data (*f)(), struct item* ap, struct item* ap1);
void ex_ddyad(data (*f)(), struct item* ap, struct item* ap1);

#endif
