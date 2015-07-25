#include <stdio.h>

int main (void)
{
   int ret = 0;
   int nblanks = 0, ntabs = 0, nnewlines = 0;
   int c = 0;

   printf("This program counts the number of blanks, tabs, newlines.\n");

   while ( (c = getchar ()) != EOF ) 
   {
      if (c == ' ') 
         ++nblanks;
      if (c == '\t') 
         ++ntabs;
      if (c == '\n')
         ++nnewlines;
   }

   printf("\nWe have %d blanks, %d tabs, %d nnewlines.\n", nblanks, ntabs, nnewlines);

   return ret;
}
