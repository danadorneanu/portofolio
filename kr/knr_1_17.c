#include <stdio.h>
#define STORED_LENGTH 80

int main (void)    
{
   int ret = 0;
   char line[STORED_LENGTH];
   int c = 0, i = 0;
   while (c != EOF )
   {
      for (i = 0; (i < STORED_LENGTH) &&  ((c = getchar()) != EOF) && (c != '\n'); ++i)
         line[i] = c;
      if (i == STORED_LENGTH)
      {
         printf("%s", line);
         while (((c = getchar()) != EOF ) && (c != '\n'))
            putchar(c);
         putchar('\n');
      }
   }
   return ret;
}

