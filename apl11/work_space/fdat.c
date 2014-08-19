/* openAPL, Copyright (C) Branko Bratkovic 2000
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

#include "apl.h"
 
fdat(f)
{
   struct stat b;
   struct tm *p, *localtime();

   fstat(f,&b);
   p = localtime(&b.st_mtime);

   printf("  %02d:%02d.%02d",p->tm_hour,p->tm_min,p->tm_sec);
   printf(" %02d/%02d/%02d",p->tm_mon+1,p->tm_mday,p->tm_year%100);
}

