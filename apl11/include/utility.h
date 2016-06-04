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

#endif // UTILITY_H
