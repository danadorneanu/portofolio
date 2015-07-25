/*! \file knr_7_6.c
 * \brief Exercise 7-6. Write a program to compare two files, printing the first line where they differ.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_LINE 256
int main(int argc, char *argv[])
{
   int ret = 0;
   FILE *f = NULL, *g = NULL;
   char f_line[MAX_LEN_LINE] = {0}, g_line[MAX_LEN_LINE] = {0};
   
   /// defining a format for using out program
   if (argc != 3)
   {
      printf("\nerror: corect usage ./exec_file f1 f2");
      exit(0);
   }

   if ((f = fopen(argv[1], "r")) == NULL)
   {
      printf("\nerror:couldn't open %s", argv[1]);
      exit(0);
   }

   if ((g = fopen(argv[2], "r")) == NULL)
   {
      printf("\nerror:couldn't open %s", argv[2]);
      exit(0);
   }

   while (1)
   {
      memset(f_line, 0, MAX_LEN_LINE);
      memset(g_line, 0, MAX_LEN_LINE);

      if ( fgets(f_line, MAX_LEN_LINE, f) == NULL)
         break;
      if ( fgets(g_line, MAX_LEN_LINE, g) == NULL)
         break;

      
      if (!strcmp(f_line, g_line))
         continue;
      else 
      {
         printf("\nFirst lines that don't match are: \n\t%s\n\t%s", f_line, g_line);
         break;
      }
   
   }

   return ret;
}

