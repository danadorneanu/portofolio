/*! \file knr_7_8.c
 * \brief Exercise 7-8. Write a program to print a set of files, starting each new one on a new page,
 * \brief with a page and a running page count for each file.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_LINE 256
#define NR_OF_ROWS_ON_PAGE 28

int main(int argc, char *argv[])
{
   int ret = 0;
   char line[MAX_LEN_LINE] = {0};
   int nr_rows = 0;
   int page = 0;
   FILE *f = NULL;
   
   printf("\nThis program prints the files given at command line at stdout, \n starting each new one on a new page, with a page and a running count \n for each file.");

   ///we check if we have any file to print
   if (argc == 1) 
   {
      printf("\nerror: Correct usage\n\t./exec_file f1 f2 ... fn");
      exit(0);
   }

   ///we skip the first argument
   while (argc --  > 1)
   {
      /// we watch if there where any problems opening one of the file
      /// if there were we just report the problem
      if ( (f = fopen(argv[argc], "r")) == NULL)
      {
         printf("\nerror: Couldn't open file: %s", argv[argc]);
         continue;
      }


      /// printf newlines after end of page in order 
      /// to start each file in a new page
      if (nr_rows)
         while ((++nr_rows % NR_OF_ROWS_ON_PAGE))
            printf("\n");

      if (page)
         printf("\n\n%d\n\n\n", ++page);

      /// we print the title only on first page of the file
      printf("\n\t\t\t\t\tTitle: %s\n\n", argv[argc]);
      page = 0;

      /// reset the line 
      memset(line, 0, MAX_LEN_LINE);
      while (fgets(line, MAX_LEN_LINE, f) != NULL)
      {
         printf("\n\t%s", line);
         memset(line, 0, MAX_LEN_LINE);
         /// if new page
         if ( ! (++nr_rows % NR_OF_ROWS_ON_PAGE) )
            printf("\n\n%d\n\n\n", ++page);
      }
   }

   /// printf newlines after end of page in order 
   /// to start each file in a new page
   if (nr_rows)
      while ((++nr_rows % NR_OF_ROWS_ON_PAGE))
         printf("\n");

   if (page)
      printf("\n\n%d\n\n\n", ++page);


   return ret;
}

