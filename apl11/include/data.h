/* data.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include "apl.h"

int access();

void bidx(struct item* ip);
int copy(int type, char* from, char* to, int size);
void colapse(int k);
void putdat(struct item* ip, data d);
void pop();
int size();

void indexIterateInit(DataIterator* iter);
bool indexIterate(DataIterator* iter);
void purge_name(SymTabEntry* np);
void erase(SymTabEntry* np);

#endif // DATA_H
