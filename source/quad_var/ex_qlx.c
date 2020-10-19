/* openAPL, Copyright (C) Branko Bratkovic 1998
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */

#include <stdio.h>
#include "apl.h"
#include "data.h"
#include "char.h"
#include "memory.h"

// Llx; latent expression.  Execute this string when a
// workspace is loaded.
// Example:  Llx { '''Hello.  Welcome to this workspace.'''
//
struct item* ex_qlx(io) int io; /* 0 = source, 1 = sink */
{
    struct item *p, *q;
    SymTabEntry* n;

    if (io == 0) {
        n = nlook(S_QUAD "lx");
        if (n) {
            q = n->itemp;
            p = dupdat(q);
            copy(q->itemType, (char*)q->datap, (char*)p->datap, q->size);
        }
        else
            p = newdat(CH, 1, 0);
        return (p);
    }
    else {

        pop();
        n = nlook(S_QUAD "lx");
        if (n == 0) { /* allocate new name: */
            //for(n=symbolTable; n->namep; n++) ;
            char name[4] = S_QUAD "lx";
            n = symtabInsert(name);
            n->itemType = LV;
            n->entryUse = 0;
            n->itemp = newdat(CH, 0, 0);
        }
        q = fetch1();
        erase(n);
        n->entryUse = DA;
        n->itemp = q;
        expr_stack_ptr[-1] = (struct item*)n;

        return (0);
    };
}
