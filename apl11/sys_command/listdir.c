/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <dirent.h> 
 
#include "apl.h"
#include "utility.h"

void listdir() {
   DIR *thisDirectory;
   struct dirent *entry;
   int i;

   thisDirectory = opendir(".");
   if (thisDirectory == 0) error(ERR_botch,"could not open CWD");
   while (1) {
      entry = readdir(thisDirectory);
      if (entry == 0) break;
      if(entry->d_ino != 0 && entry->d_name[0] != '.') {
         if (column+10 >= pagewidth) printf("\n\t");
         for (i=0; i<14 && entry->d_name[i]; i++) putchar(entry->d_name[i]);
         putchar('\t');
      }
   }
   putchar('\n');
   closedir(thisDirectory);
}
