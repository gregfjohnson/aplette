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
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"

struct item* ex_qquad(int io)
{
    int i;
    struct item* p;
    char *iline, *getinput();

    switch (io) {
    case QV_source:
        iline = getinput(quote_quad_prompt);
        if (!isatty(0))
            printf("%s", iline);
        if (iline == NULL)
            error(ERR, "user input was null");
        for (i = 0; iline[i] != '\n'; i++)
            ;
        p = newdat(CH, 1, i);
        copy(CH, (char*)iline, (char*)p->datap, i);
        aplfree((int*)iline);
        iline = (char*)NULL;
        quote_quad_prompt[0] = '\0';
        return (p);
        break;

    case QV_sink:
        pop();
        p = fetch1();
        if (p->type != CH)
            error(ERR_domain, "assign value not character");
        if (p->rank > 1)
            error(ERR_rank, "rank of assign value too large");
        if (p->size > quote_quad_limit)
            error(ERR_limit, "assign value too long");
        if (quote_quad_prompt[0] != '\0')
            error(ERR_limit, "quote quad prompt not empty");
        copy(CH, (char*)p->datap, (char*)&quote_quad_prompt, p->size);
        quote_quad_prompt[p->size] = '\0';
        return (0);
    }
}
