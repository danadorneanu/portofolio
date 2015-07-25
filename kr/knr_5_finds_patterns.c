/* find: print lines that match pattern from 1st arg */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char *line, int max);

int main(int argc, char *argv[])
{
   char line[MAXLINE] = {};
   int found = 0;
   
   printf("\nThis program finds a pattern into the input lines\nThe patern is give as a command line arguments.");

   if (argc != 2)
      printf("erorr: The correct usage is: ./exac_name pattern_to_find \n");
   else
      while (getline(line, MAXLINE) > 0)
         if (strstr(line, argv[1]) != NULL) 
         {
            printf("%s", line);
            found++;
         }
   return found;
}

int getline(char *s, int lim)
{
   int c = 0, i = 0;

   for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); i++)
      *s++ = c;

   if (c == '\n') 
      *s++ = c;

   *++s = '\0';
   
   return i;
}

