#include<stdio.h>
#define MAX_LENGTH 30

int getline (char line[], int maxline);
void copy (char source[], char dest[]);

int main (void)
{
   int ret = 0;
   int crLength = 0, maxSoFar = 0;
   char crLine[MAX_LENGTH];
   char longestLine[MAX_LENGTH];

   while ((crLength = getline(crLine, MAX_LENGTH)) > 0)
      if (crLength > maxSoFar) 
      {
         maxSoFar = crLength;
         copy(crLine, longestLine);
      }
   if (maxSoFar > 0)
      printf("The longesc line '%s[...]' has %d chars", longestLine, maxSoFar);

   return ret;
}

int getline (char line[], int maxline)
{
   int c = 0, i = 0;

   for (i = 0; (i < maxline - 1) && ((c = getchar()) !=EOF) && (c != '\n'); ++i)
   {
      line[i] = c;
   }
   if (c == '\n') 
   {
      line[i] = c;
      ++i;
   }
   else if (i == (maxline - 1))
   {
      line[i] = '\0';
      while( ((c = getchar()) != EOF) && (c!='\n')) 
         ++i;
   }

   return i;
}

void copy (char source[], char dest[])
{
   int i = 0;

   for(;(dest[i] = source[i]) != '\0'; ++i);
}


