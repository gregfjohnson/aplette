/* userfunc.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef USERFUNC_H
#define USERFUNC_H

#include "apl.h"

void tback(int flag);
void sichk(struct nlist *n);
void ex_nilret();
void funwrite(char *fname);
void funedit(char *fname);
int  funread(char *fname);
void funcomp(struct nlist *np);
void ex_ibr0();
void eval_qlx();

#endif
