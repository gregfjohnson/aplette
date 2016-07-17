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
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>
#include "apl.h"
#include "utility.h"

struct item* ex_qai(io) int io; /* 0 = source, 1 = sink */
{
    struct tms t;
    struct item* p;
    long tv;

    if (io == 0) {
        time(&tv);
        times(&t);
        p = newdat(DA, 1, 4);
        p->datap[0] = (data)geteuid();
        p->datap[1] = t.tms_utime + t.tms_cutime;
        p->datap[3] = tv - startTime;
        p->datap[2] = t.tms_stime + t.tms_cstime;
        return (p);
    }
    else {
        error(ERR_implicit, "cannot change accounting info");
    };
}
