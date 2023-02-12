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
void ex_dscal(int m, data (*f)(), item_t* p1, item_t* p2);

void ex_cdyad(data (*f)(), item_t* ap, item_t* ap1);
void ex_mdyad(data (*f)(), item_t* ap, item_t* ap1);
void ex_ddyad(data (*f)(), item_t* ap, item_t* ap1);

#endif
