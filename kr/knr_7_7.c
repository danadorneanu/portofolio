/*! \file knr_7_7.c
 * \brief find: print lines that match pattern from 1st arg 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_LINE 256

int main(int argc, char *argv[])
{
   char line[MAX_LEN_LINE] = {0};
   int found = 0;
   FILE *f = NULL;
   
   printf("\nThis program finds a pattern into the input lines\nThe patern is give as a command line arguments.");

   /// we check if we have any pattern to find
   if (argc < 2) 
   {
      printf("\nerror: Correct usage\n\t./exec_file pattern [optional] named_files_where_to_find_pattern");
      exit(0);
   }

   /// we skip the first 2 argumets 
   while (argc --  > 2)
   {
      /// we watch if there where any problems opening one of the file
      /// if there were we just report the problem
      if ( (f = fopen(argv[argc], "r")) == NULL)
      {
         printf("\nerror: Couldn't open file: %s", argv[argc]);
         continue;
      }
      /// reset the number of matches
      found = 0;
      /// set the line to have only zeros
      memset(line, 0, MAX_LEN_LINE);
      while (fgets(line, MAX_LEN_LINE, f) != NULL)
      {
         if (strstr(line, argv[1]) != NULL)
         {
            /// we print the name of the file for the first match
            if (!found)
               printf("\nIn file %s", argv[argc]);
            ///we print the line where we found any match
            printf("\n\t%s", line);
            /// set the line to have only zeros
            memset(line, 0, MAX_LEN_LINE);
            ///we increment the number of matches for current file
            found++;
         }
      }
   }
   return found;
}

