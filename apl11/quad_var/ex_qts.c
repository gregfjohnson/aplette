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
/* #include <unistd.h> */
#include "apl.h"

struct item * ex_qts(io)
int io; /* 0 = source, 1 = sink */
{
struct item *p;
struct tm *tp;
struct timeval tv;
struct timezone tz;
long tvec;
   
   if ( io == 0 ) { 
      p = newdat(DA, 1, 7);

      /* get time information from the OS */
      time(&tvec);
      tp = localtime(&tvec);
      gettimeofday(&tv, &tz);

      /* load time into item *p */
      p->datap[0]=tp->tm_year+1900;
      p->datap[1]=tp->tm_mon+1;
      p->datap[2]=tp->tm_mday;
      p->datap[3]=tp->tm_hour;
      p->datap[4]=tp->tm_min;
      p->datap[5]=tp->tm_sec;
      p->datap[6]=tv.tv_usec/1000;
             
      return(p);

   } else {
      error(ERR_implicit,"cannot change time");
   };
}
